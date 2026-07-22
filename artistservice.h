#ifndef ARTISTSERVICE_H
#define ARTISTSERVICE_H

#include "artistrepository.h"
#include "songrepository.h"
#include "albumrepository.h"
#include "playlistrepository.h"
#include "listenerrepository.h"

class ArtistService
{
private:
    ArtistRepository& artistRepository;
    SongRepository& songRepository;
    AlbumRepository& albumRepository;
    PlaylistRepository& playlistRepository;
    ListenerRepository& listenerRepository;

public:
    ArtistService(ArtistRepository& artistRepository,
                  SongRepository& songRepository,
                  AlbumRepository& albumRepository,
                  PlaylistRepository& playlistRepository,
                  ListenerRepository& listenerRepository);

    bool createAlbum(const Album& album);

    bool createSong(const Song& song);

    bool deleteAlbum(int albumId);

    bool deleteSong(int trackId);

    bool editAlbum(const Album& album);

    bool editSong(const Song& song);

    vector<Album> getAlbums(int artistId);

    vector<Song> getAlbumSongs(int albumId);

    vector<Song> getSingles(int artistId);

    bool deleteArtist(int artistId);

};

#endif // ARTISTSERVICE_H
