#include "artistservice.h"
#include "spotifyexception.h"

ArtistService::ArtistService(ArtistRepository& artistRepository,
                             SongRepository& songRepository,
                             AlbumRepository& albumRepository)
    : artistRepository(artistRepository),
    songRepository(songRepository),
    albumRepository(albumRepository)
{
}

bool ArtistService::createAlbum(const Album& album)
{
    std::optional<Artist> artist = artistRepository.search(album.getArtistId());

    if (!artist.has_value())
        throw SpotifyException("Artist not found.");

    albumRepository.save(album);

    return true;
}
bool ArtistService::createSong(const Song& song)
{
    std::optional<Artist> artist =
        artistRepository.search(song.getArtistId());

    if (!artist.has_value())
        throw SpotifyException("Artist not found.");

    if (song.getAlbumId() != 0)
    {
        std::optional<Album> album = albumRepository.search(song.getAlbumId());

        if (!album.has_value())
            throw SpotifyException("Album not found.");
    }

    songRepository.save(song);

    return true;
}

bool ArtistService::editAlbum(const Album& album)
{
    std::optional<Album> oldAlbum = albumRepository.search(album.getAlbumId());

    if (!oldAlbum.has_value())
        throw SpotifyException("Album not found.");

    albumRepository.save(album);

    return true;
}
bool ArtistService::editSong(const Song& song)
{
    std::optional<Song> oldSong = songRepository.search(song.getTrackId());

    if (!oldSong.has_value())
        throw SpotifyException("Song not found.");

    if (song.getAlbumId() != 0)
    {
        std::optional<Album> album = albumRepository.search(song.getAlbumId());

        if (!album.has_value())
            throw SpotifyException("Album not found.");
    }

    songRepository.save(song);

    return true;
}
bool ArtistService::deleteSong(int trackId)
{
    std::optional<Song> song = songRepository.search(trackId);

    if (!song.has_value())
        throw SpotifyException("Song not found.");

    songRepository.remove(trackId);

    return true;
}
bool ArtistService::deleteAlbum(int albumId)
{
    std::optional<Album> album = albumRepository.search(albumId);

    if (!album.has_value())
        throw SpotifyException("Album not found.");

    std::vector<Song> songs = songRepository.getByAlbum(albumId);

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        songRepository.remove(songs[i].getTrackId());
    }

    albumRepository.remove(albumId);

    return true;
}
vector<Album> ArtistService::getAlbums(int artistId)
{
    return albumRepository.getByArtist(artistId);
}
vector<Song> ArtistService::getAlbumSongs(int albumId)
{
    return songRepository.getByAlbum(albumId);
}
vector<Song> ArtistService::getSingles(int artistId)
{
    return songRepository.singleSongs(artistId);
}