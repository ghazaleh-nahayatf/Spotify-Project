#include "listenerservice.h"
#include "spotifyexception.h"
#include "artistrepository.h"

ListenerService::ListenerService(
    ListenerRepository& listenerRepository,
    PlaylistRepository& playlistRepository,
    SongRepository& songRepository,
    ArtistRepository& artistRepository)
    : listenerRepository(listenerRepository),
    playlistRepository(playlistRepository),
    songRepository(songRepository),
    artistRepository(artistRepository)
{
}
bool ListenerService::createPlaylist(const Playlist &playlist)
{
    if (!listenerRepository.search(playlist.getListenerId()).has_value())
        throw SpotifyException("Listener not found.");

    vector<Playlist> playlists = playlistRepository.getByListener(playlist.getListenerId());

    for(int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if(playlists[i].getPlaylistName() ==
            playlist.getPlaylistName())
        {
            throw SpotifyException("Playlist name already exists.");
        }
    }
    playlistRepository.save(playlist);
    return true;
}
bool ListenerService::editPlaylist(const Playlist& playlist)
{
    if (!playlistRepository.search(playlist.getPlaylistId()).has_value())
        throw SpotifyException("Playlist not found.");

    playlistRepository.save(playlist);

    return true;
}
bool ListenerService::deletePlaylist(int playlistId)
{
    if (!playlistRepository.search(playlistId).has_value())
        throw SpotifyException("Playlist not found.");

    playlistRepository.remove(playlistId);

    return true;
}
bool ListenerService::addSongToPlaylist(int playlistId, int trackId)
{
    if (!playlistRepository.search(playlistId).has_value())
        throw SpotifyException("Playlist not found.");

    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    if (!playlistRepository.addSong(playlistId, trackId))
        throw SpotifyException("Song already exist.");

    playlistRepository.addSong(playlistId, trackId);

    return true;
}
bool ListenerService::removeSongFromPlaylist(int playlistId, int trackId)
{
    if (!playlistRepository.search(playlistId).has_value())
        throw SpotifyException("Playlist not found.");

    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    if (!playlistRepository.removeSong(playlistId, trackId))
        throw SpotifyException("Song does not exist in playlist.");

    return true;
}
bool ListenerService::likeSong(int listenerId, int trackId)
{
    if (!listenerRepository.search(listenerId).has_value())
        throw SpotifyException("Listener not found.");

    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    listenerRepository.updateLiked(listenerId, trackId, true);

    int favoriteId = playlistRepository.getFavoritePlaylistId(listenerId);

    playlistRepository.addSong(favoriteId, trackId);

    return true;
}
bool ListenerService::unlikeSong(int listenerId, int trackId)
{
    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    listenerRepository.updateLiked(listenerId, trackId, false);
    int favoriteId = playlistRepository.getFavoritePlaylistId(listenerId);

    playlistRepository.removeSong(favoriteId, trackId);
    return true;
}
vector<Playlist> ListenerService::getPlaylists(int listenerId)
{
    return playlistRepository.getByListener(listenerId);
}
vector<Artist> ListenerService::getArtists()
{
    return artistRepository.getAll();
}
vector<Song> ListenerService::getPlaylistSongs(int playlistId)
{
    if (!playlistRepository.search(playlistId).has_value())
        throw SpotifyException("Playlist not found.");

    vector<Song> songs;

    vector<int> ids = playlistRepository.getSongIds(playlistId);

    for (int i = 0; i < static_cast<int>(ids.size()); i++)
    {
        optional<Song> song = songRepository.search(ids[i]);

        if (song.has_value())
            songs.push_back(song.value());
    }

    return songs;
}
bool ListenerService::deleteListener(int listenerId)
{
    if (!listenerRepository.search(listenerId).has_value())
        throw SpotifyException("Listener not found.");

    vector<Playlist> playlists = playlistRepository.getByListener(listenerId);

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        playlistRepository.remove(playlists[i].getPlaylistId());
    }

    listenerRepository.remove(listenerId);

    return true;
}
bool ListenerService::isLiked(int listenerId, int trackId)
{
    return listenerRepository.isLiked(listenerId, trackId);
}
vector<Song> ListenerService::getAllSongs()
{
    return songRepository.getAll();
}
Song ListenerService::getSong(int trackId)
{
    std::optional<Song> song = songRepository.search(trackId);

    if(!song.has_value())
        throw SpotifyException("Song not found.");

    return song.value();
}
Playlist ListenerService::getPlaylist(int playlistId)
{
    optional<Playlist> playlist =
        playlistRepository.search(playlistId);

    if(!playlist.has_value())
    {
        throw SpotifyException("Playlist not found.");
    }

    return playlist.value();
}
Listener ListenerService::getListener(int listenerId)
{
    std::optional<Listener> listener =
        listenerRepository.search(listenerId);

    if(!listener.has_value())
        throw SpotifyException("Listener not found.");

    return listener.value();
}
bool ListenerService::editProfile(const Listener& listener)
{
    std::optional<Listener> oldListener =listenerRepository.search(listener.getListenerId());

    if(!oldListener.has_value())
        throw SpotifyException("Listener not found.");

    std::optional<Account> account =
        listenerRepository.searchByUserName(listener.getUserName());

    if(account.has_value() &&
        account->getAccountId() != listener.getListenerId())
    {
        throw SpotifyException("Username already exists.");
    }

    listenerRepository.update(listener);

    return true;
}

vector<Song> ListenerService::recommendSongs(int listenerId)
{
    if (!listenerRepository.search(listenerId).has_value())
        throw SpotifyException("Listener not found.");

    int favoriteId = playlistRepository.getFavoritePlaylistId(listenerId);

    vector<Song> favoriteSongs = getPlaylistSongs(favoriteId);

    if (favoriteSongs.empty())
        return {};

    map<string, int> genres;

    for (int i = 0; i < static_cast<int>(favoriteSongs.size()); i++)
    {
        genres[favoriteSongs[i].getGenre()]++;
    }

    string favoriteGenre = favoriteSongs[0].getGenre();
    int maxCount = 0;

    vector<string> checkedGenres;

    for (int i = 0; i < static_cast<int>(favoriteSongs.size()); i++)
    {
        string currentGenre = favoriteSongs[i].getGenre();

        bool checked = false;

        for (int j = 0; j < static_cast<int>(checkedGenres.size()); j++)
        {
            if (checkedGenres[j] == currentGenre)
            {
                checked = true;
                break;
            }
        }

        if (checked)
            continue;

        checkedGenres.push_back(currentGenre);

        int count = 0;

        for (int j = 0; j < static_cast<int>(favoriteSongs.size()); j++)
        {
            if (favoriteSongs[j].getGenre() == currentGenre)
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            favoriteGenre = currentGenre;
        }
    }

    vector<Song> allSongs = songRepository.getAll();

    vector<Song> result;

    for (int i = 0; i < static_cast<int>(allSongs.size()); i++)
    {
        if (allSongs[i].getGenre() != favoriteGenre)
            continue;

        bool liked = false;

        for (int j = 0; j < static_cast<int>(favoriteSongs.size()); j++)
        {
            if (allSongs[i].getTrackId() ==
                favoriteSongs[j].getTrackId())
            {
                liked = true;
                break;
            }
        }

        if (!liked)
            result.push_back(allSongs[i]);
    }

    return result;
}