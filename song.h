#ifndef SONG_H
#define SONG_H
#include<string>
using namespace std;

class Song
{
private:
    string songName;
    int releaseYear;
    string genre;
    string filePath;
    int trackId;
    int artistId;
    int albumId;

public:
    Song();
    Song(string songName,
         int releaseYear,
         string genre,
         string filePath,
         int trackId,
         int artistId,
         int albumId);

    virtual ~Song() {}
};

#endif // SONG_H
