#include "listenerservice.h"
#include "spotifyexception.h"

ListenerService::ListenerService(ListenerRepository& listenerRepository,
                                 PlaylistRepository& playlistRepository,
                                 SongRepository& songRepository)
    : listenerRepository(listenerRepository),
    playlistRepository(playlistRepository),
    songRepository(songRepository)

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

    playlistRepository.addSong(playlistId, trackId);

    return true;
}
bool ListenerService::removeSongFromPlaylist(int playlistId, int trackId)
{
    if (!playlistRepository.search(playlistId).has_value())
        throw SpotifyException("Playlist not found.");

    playlistRepository.removeSong(playlistId, trackId);

    return true;
}
bool ListenerService::likeSong(int listenerId, int trackId)
{
    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    listenerRepository.updateLiked(listenerId, trackId, true);

    return true;
}
bool ListenerService::unlikeSong(int listenerId, int trackId)
{
    if (!songRepository.search(trackId).has_value())
        throw SpotifyException("Song not found.");

    listenerRepository.updateLiked(listenerId, trackId, false);

    return true;
}
vector<Playlist> ListenerService::getPlaylists(int listenerId)
{
    return playlistRepository.getByListener(listenerId);
}