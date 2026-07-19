#ifndef ALBUMFILEMANGER_H
#define ALBUMFILEMANGER_H

#include<vector>
#include "album.h"

using namespace std;

class AlbumFileManager
{
public:
    static void save(const vector<Album>& songs);

    static vector<Album> load();
};

#endif // ALBUMFILEMANGER_H
