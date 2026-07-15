#ifndef ALBUM_H
#define ALBUM_H
#include<string>
using namespace std;

class Album
{
private:
    string albumName;
    int albumId;
    int artistId;
public:
    Album();
    Album(string albumName,
          int albumId,
          int artistId);

    virtual ~Album(){}
};

#endif // ALBUM_H
