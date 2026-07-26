#ifndef PLAYLISTDATA_H
#define PLAYLISTDATA_H
#include <vector>
#include <map>

#include "playlist.h"

struct PlaylistData
{
    std::vector<Playlist> playlists;
    std::map<int, std::vector<int>> playlistSongs;
};

#endif // PLAYLISTDATA_H
