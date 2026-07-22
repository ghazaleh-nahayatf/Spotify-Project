#include "commonservice.h"

CommonService::CommonService(SongRepository& songRepository,
                             AlbumRepository& albumRepository,
                             ArtistRepository& artistRepository,
                             PlaylistRepository& playlistRepository)
    : songRepository(songRepository),
    albumRepository(albumRepository),
    artistRepository(artistRepository),
    playlistRepository(playlistRepository)
{}

vector<Song> CommonService::searchSong(string songName)
{
    vector<Song> result;

    vector<Song> songs = songRepository.getAll();

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if (songs[i].getName().find(songName) != string::npos)
        {
            result.push_back(songs[i]);
        }
    }

    return result;
}
vector<Artist> CommonService::searchArtist(string artistName)
{
    vector<Artist> result;

    vector<Artist> artists = artistRepository.getAll();

    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getFullName().find(artistName) != string::npos)
            result.push_back(artists[i]);
    }

    return result;
}
vector<Album> CommonService::searchAlbum(string albumName)
{
    vector<Album> result;

    vector<Album> albums = albumRepository.getAll();

    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if (albums[i].getAlbumName().find(albumName) != string::npos)
            result.push_back(albums[i]);
    }

    return result;
}
vector<Song> CommonService::filterByGenre(string genre)
{
    vector<Song> result;

    vector<Song> songs = songRepository.getAll();

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if (songs[i].getGenre() == genre)
            result.push_back(songs[i]);
    }

    return result;
}
vector<Song> CommonService::filterByYear(int year)
{
    vector<Song> result;

    vector<Song> songs = songRepository.getAll();

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if (songs[i].getReleaseYear() == year)
            result.push_back(songs[i]);
    }

    return result;
}
vector<Song> CommonService::sortSongsByName()
{
    vector<Song> songs = songRepository.getAll();

    for (int i = 0; i < static_cast<int>(songs.size()) - 1; i++)
    {
        for (int j = i + 1; j < static_cast<int>(songs.size()); j++)
        {
            if (songs[i].getName() > songs[j].getName())
            {
                Song temp = songs[i];
                songs[i] = songs[j];
                songs[j] = temp;
            }
        }
    }

    return songs;
}
vector<Song> CommonService::sortSongsByYear()
{
    vector<Song> songs = songRepository.getAll();

    for (int i = 0; i < static_cast<int>(songs.size()) - 1; i++)
    {
        for (int j = i + 1; j < static_cast<int>(songs.size()); j++)
        {
            if (songs[i].getReleaseYear() > songs[j].getReleaseYear())
            {
                Song temp = songs[i];
                songs[i] = songs[j];
                songs[j] = temp;
            }
        }
    }

    return songs;
}
vector<Album> CommonService::sortAlbumsByName()
{
    vector<Album> albums = albumRepository.getAll();

    for (int i = 0; i < static_cast<int>(albums.size()) - 1; i++)
    {
        for (int j = i + 1; j < static_cast<int>(albums.size()); j++)
        {
            if (albums[i].getAlbumName() > albums[j].getAlbumName())
            {
                Album temp = albums[i];
                albums[i] = albums[j];
                albums[j] = temp;
            }
        }
    }

    return albums;
}
vector<Playlist> CommonService::sortPlaylistsByName()
{
    vector<Playlist> playlists = playlistRepository.getAll();

    for (int i = 0; i < static_cast<int>(playlists.size()) - 1; i++)
    {
        for (int j = i + 1; j < static_cast<int>(playlists.size()); j++)
        {
            if (playlists[i].getPlaylistName() > playlists[j].getPlaylistName())
            {
                Playlist temp = playlists[i];
                playlists[i] = playlists[j];
                playlists[j] = temp;
            }
        }
    }

    return playlists;
}