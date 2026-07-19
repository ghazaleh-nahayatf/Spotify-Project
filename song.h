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
    int trackId = 0;
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

    string getName() const;
    int getReleaseYear() const;
    string getGenre() const;
    string getFilePath() const;
    int getTrackId() const;
    int getArtistId() const;
    int getAlbumId() const;

    void setName(string newName);
    void setReleaseYear(int newYear);
    void setGenre(string newGenre);
    void setFilePath(string newPath);
    void setTrackId(int newId);
    void setArtistId(int newId);
    void setAlbumId(int newId);

    string serialize() const;
    static Song deserialize(const string& line);

    virtual ~Song() {}
};

#endif // SONG_H
