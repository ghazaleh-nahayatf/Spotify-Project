#include "playlist.h"

Playlist::Playlist() {}

Playlist::Playlist(const string& playlistName,
                   int playlistId,
                   int listenerId)
    : playlistName(playlistName),
    playlistId(playlistId),
    listenerId(listenerId)
{
}
int Playlist::getPlaylistId()
{
    return playlistId;
}