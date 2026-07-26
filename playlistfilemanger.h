#ifndef PLAYLISTFILEMANGER_H
#define PLAYLISTFILEMANGER_H

#include<vector>
#include "playlist.h"
#include "PlaylistData.h"

using namespace std;

class PlaylistFileManager
{
public:
    static void save(
        const std::vector<Playlist>& playlists,
        const std::map<int,std::vector<int>>& playlistSongs);

    static PlaylistData load();
};

#endif // PLAYLISTFILEMANGER_H
