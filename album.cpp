#include "album.h"

Album::Album() {}

Album::Album(string albumName,
      int albumId,
      int artistId)
    : albumName(albumName),
    albumId(albumId),
    artistId(artistId){}

string Album::getAlbumName() const
{
    return albumName;
}
int Album::getAlbumId() const
{
    return albumId;
}
int Album::getArtistId() const
{
    return artistId;
}
void Album::setAlbumId(int newId)
{
    this->albumId = newId;
}