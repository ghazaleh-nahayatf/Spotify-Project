#include "playlistrepository.h"
#include "playlistfilemanger.h"

PlaylistRepository::PlaylistRepository()
{
    playlists = PlaylistFileManager::load();

    nextPlaylistId = 1;

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if (playlists[i].getPlaylistId() >= nextPlaylistId)
            nextPlaylistId = playlists[i].getPlaylistId() + 1;
    }
}
optional<int> PlaylistRepository::save(const Playlist& entity)
{
    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if (playlists[i].getPlaylistId() == entity.getPlaylistId())
        {
            playlists[i] = entity;
            PlaylistFileManager::save(playlists);
            return playlists[i].getPlaylistId();
        }
    }

    Playlist newPlaylist = entity;
    newPlaylist.setPlaylistId(nextPlaylistId++);

    playlists.push_back(newPlaylist);

    PlaylistFileManager::save(playlists);

    return newPlaylist.getPlaylistId();
}
bool PlaylistRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if (playlists[i].getPlaylistId() == id)
        {
            playlists.erase(playlists.begin() + i );
            PlaylistFileManager::save(playlists);
            return true;
        }
    }
    return false;
}
optional<Playlist> PlaylistRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if(playlists[i].getPlaylistId() == id)
        {
            return playlists[i];
        }
    }
    return nullopt;
}
vector<Playlist> PlaylistRepository::getByListener(int listenerId)
{
    vector<Playlist> result;

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if(playlists[i].getListenerId() == listenerId)
        {
            result.push_back(playlists[i]);
        }
    }

    return result;
}