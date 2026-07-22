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
            playlists.erase(playlists.begin() + i);

            playlistSongs.erase(id);

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
bool PlaylistRepository::addSong(int playlistId, int trackId)
{
    for (int i = 0; i < static_cast<int>(playlistSongs[playlistId].size()); i++)
    {
        if (playlistSongs[playlistId][i] == trackId)
            return false;
    }

    playlistSongs[playlistId].push_back(trackId);

    return true;
}
bool PlaylistRepository::removeSong(int playlistId, int trackId)
{
    if (!search(playlistId).has_value())
        return false;

    for (int i = 0; i < static_cast<int>(playlistSongs[playlistId].size()); i++)
    {
        if (playlistSongs[playlistId][i] == trackId)
        {
            playlistSongs[playlistId].erase(
                playlistSongs[playlistId].begin() + i);

            return true;
        }
    }

    return false;
}
int PlaylistRepository::getFavoritePlaylistId(int listenerId)
{
    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        if (playlists[i].getListenerId() == listenerId &&
            playlists[i].getPlaylistName() == "Favorites")
        {
            return playlists[i].getPlaylistId();
        }
    }

    return -1;
}
vector<int> PlaylistRepository::getSongIds(int playlistId)
{
    return playlistSongs[playlistId];
}
bool PlaylistRepository::removeSongFromAllPlaylists(int trackId)
{
    bool removed = false;

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        int playlistId = playlists[i].getPlaylistId();

        for (int j = 0; j < static_cast<int>(playlistSongs[playlistId].size()); j++)
        {
            if (playlistSongs[playlistId][j] == trackId)
            {
                playlistSongs[playlistId].erase(
                    playlistSongs[playlistId].begin() + j);

                removed = true;
                j--;
            }
        }
    }

    return removed;
}
vector<Playlist> PlaylistRepository::getAll()
{
    return playlists;
}