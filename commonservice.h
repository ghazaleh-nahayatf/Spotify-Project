#ifndef COMMONSERVICE_H
#define COMMONSERVICE_H

#include "songrepository.h"
#include "albumrepository.h"
#include "artistrepository.h"
#include "playlistrepository.h"

class CommonService
{
private:
    SongRepository& songRepository;
    AlbumRepository& albumRepository;
    ArtistRepository& artistRepository;
    PlaylistRepository& playlistRepository;

public:
    CommonService(SongRepository& songRepository,
                  AlbumRepository& albumRepository,
                  ArtistRepository& artistRepository,
                  PlaylistRepository& playlistRepository);

    vector<Song> searchSong(string songName);

    vector<Artist> searchArtist(string artistName);

    vector<Album> searchAlbum(string albumName);

    vector<Song> filterByGenre(string genre);

    vector<Song> filterByYear(int year);

    vector<Song> sortSongsByName();

    vector<Song> sortSongsByYear();

    vector<Album> sortAlbumsByName();

    vector<Playlist> sortPlaylistsByName();
};

#endif // COMMONSERVICE_H
