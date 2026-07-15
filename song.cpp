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