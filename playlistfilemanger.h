#ifndef PLAYLISTFILEMANGER_H
#define PLAYLISTFILEMANGER_H

#include<vector>
#include "playlist.h"

using namespace std;

class PlaylistFileManager
{
public:
    static void save(const vector<Playlist>& playlists);

    static vector<Playlist> load();
};

#endif // PLAYLISTFILEMANGER_H
