#include "album.h"

Album::Album() {}

Album::Album(string albumName,
      int albumId,
      int artistId)
    : albumName(albumName),
    albumId(albumId),
    artistId(artistId){}