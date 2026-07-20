#ifndef ARTISTFILEMANGER_H
#define ARTISTFILEMANGER_H

#include "artist.h"
#include <vector>

using namespace std;

class ArtistFileManager
{
public:
    static void save(const vector<Artist>& artists);

    static vector<Artist> load();
};

#endif // ARTISTFILEMANGER_H
