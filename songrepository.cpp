#include "songrepository.h"
#include "songfilemanager.h"
#include "song.h"
SongRepository::SongRepository()
{
   songs = SongFileManager::load();
    nextTrackId = 1;

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if(songs[i].getTrackId() >= nextTrackId)
            nextTrackId = songs[i].getTrackId() + 1;
    }
}

optional<int> SongRepository::save(const Song& entity)
{
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if (songs[i].getTrackId() == entity.getTrackId())
        {
            songs[i] = entity;
            SongFileManager::save(songs);
            return songs[i].getTrackId();
        }
    }

    Song newSong = entity;
    newSong.setTrackId(nextTrackId++);

    songs.push_back(newSong);

    SongFileManager::save(songs);

    return newSong.getTrackId();
}
bool SongRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if (songs[i].getTrackId() == id)
        {
            songs.erase(songs.begin() + i );
            SongFileManager::save(songs);
            return true;
        }
    }
    return false;
}
optional<Song> SongRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if(songs[i].getTrackId() == id)
        {
            return songs[i];
        }
    }
    return nullopt;
}
vector<Song> SongRepository::singleSongs(int artistId)
{
    vector<Song>result;
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if(songs[i].getArtistId() == artistId && songs[i].getAlbumId()==0 )
        {
            result.push_back(songs[i]);
        }
    }
    return result;
}
vector<Song> SongRepository::getByAlbum(int albumId)
{
    vector<Song>result;
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if(songs[i].getAlbumId() == albumId)
        {
            result.push_back(songs[i]);
        }
    }
    return result;
}
vector<Song> SongRepository::getByArtist(int artistId)
{
    vector<Song>result;
    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        if(songs[i].getArtistId() == artistId)
        {
            result.push_back(songs[i]);
        }
    }
    return result;
}

vector<Song> SongRepository::getAll()
{
    return songs;
}





















