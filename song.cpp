#include "song.h"

Song::Song()
{
    albumId = 0;
}

Song::Song(string songName,
           int releaseYear,
           string genre,
           string filePath,
           int trackId,
           int artistId,
           int albumId)
    : songName(songName),
    releaseYear(releaseYear),
    genre(genre),
    filePath(filePath),
    trackId(trackId),
    artistId(artistId),
    albumId(albumId)
{
}

int Song::getAlbumId() const
{
    return albumId;
}
int Song::getArtistId() const
{
    return artistId;
}
int Song::getTrackId() const
{
    return trackId;
}
string Song::getFilePath() const
{
    return filePath;
}
string Song::getGenre() const
{
    return genre;
}
string Song::getName() const
{
    return songName;
}
int Song::getReleaseYear() const
{
    return releaseYear;
}

void Song::setAlbumId(int newId)
{
    this->albumId=newId;
}
void Song::setArtistId(int newId)
{
    this->artistId=newId;
}
void Song::setTrackId(int newId)
{
    this->trackId=newId;
}
void Song::setReleaseYear(int newYear)
{
    this->releaseYear=newYear;
}
void Song::setFilePath(string newPath)
{
    this->filePath=newPath;
}
void Song::setGenre(string newGenre)
{
    this->genre=newGenre;
}
void Song::setName(string newName)
{
    this->songName=newName;
}















