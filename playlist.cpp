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
string Playlist::getPlaylistName() const
{
    return playlistName;
}
int Playlist::getPlaylistId() const
{
    return playlistId;
}
int Playlist::getListenerId() const
{
    return listenerId;
}
void Playlist::setPlaylistId(int newId)
{
    this->playlistId = newId;
}
void Playlist::setPlaylistName(string name)
{
    this->playlistName = name;
}
void Playlist::setListenerId(int newId)
{
    this->listenerId = newId;
}
