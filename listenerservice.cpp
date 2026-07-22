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

    if (!playlistRepository.addSong(playlistId, trackId))
        throw SpotifyException("Song doesnot exist.");

    playlistRepository.removeSong(playlistId, trackId);

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