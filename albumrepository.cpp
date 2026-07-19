#include "albumrepository.h"
#include "albumfilemanger.h"
#include "album.h"

AlbumRepository::AlbumRepository()
{
    albums = AlbumFileManager::load();
    nextAlbumId = 1;

    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if(albums[i].getAlbumId() >= nextAlbumId)
            nextAlbumId = albums[i].getAlbumId() + 1;
    }
}
optional<int> AlbumRepository::save(const Album& entity)
{
    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if (albums[i].getAlbumId() == entity.getAlbumId())
        {
            albums[i] = entity;
            AlbumFileManager::save(albums);
            return albums[i].getAlbumId();
        }
    }

    Album newAlbum = entity;
    newAlbum.setAlbumId(nextAlbumId++);

    albums.push_back(newAlbum);

    AlbumFileManager::save(albums);

    return newAlbum.getAlbumId();
}
bool AlbumRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if (albums[i].getAlbumId() == id)
        {
            albums.erase(albums.begin() + i );
            AlbumFileManager::save(albums);
            return true;
        }
    }
    return false;
}
optional<Album> AlbumRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if(albums[i].getAlbumId() == id)
        {
            return albums[i];
        }
    }
    return nullopt;
}
vector<Album> AlbumRepository::getByArtist(int artistId)
{

    vector<Album>result;
    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        if(albums[i].getArtistId() == artistId)
        {
            result.push_back(albums[i]);
        }
    }
    return result;
}