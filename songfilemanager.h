#ifndef SONGFILEMANAGER_H
#define SONGFILEMANAGER_H
#include<vector>
#include "song.h"
using namespace std;

class SongFileManager
{
public:
    static void save(const vector<Song>& songs);

    static vector<Song> load();
};

#endif // SONGFILEMANAGER_H
