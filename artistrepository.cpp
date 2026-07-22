#include "artistrepository.h"
#include "artistfilemanger.h"

ArtistRepository::ArtistRepository()
{
    artists = ArtistFileManager::load();

    nextArtistId = 1;

    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getArtistId() >= nextArtistId)
            nextArtistId = artists[i].getArtistId() + 1;
    }
}

std::optional<int> ArtistRepository::save(const Artist& entity)
{
    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getArtistId() == entity.getArtistId())
        {
            artists[i] = entity;
            ArtistFileManager::save(artists);
            return artists[i].getArtistId();
        }
    }

    Artist newArtist = entity;
    newArtist.setArtistId(nextArtistId++);

    artists.push_back(newArtist);

    ArtistFileManager::save(artists);

    return newArtist.getArtistId();
}

bool ArtistRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getArtistId() == id)
        {
            artists.erase(artists.begin() + i);

            ArtistFileManager::save(artists);

            return true;
        }
    }

    return false;
}

std::optional<Artist> ArtistRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getArtistId() == id)
            return artists[i];
    }

    return std::nullopt;
}

std::optional<Account> ArtistRepository::searchByUserName(
    const std::string& username)
{
    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        if (artists[i].getUserName() == username)
            return artists[i];
    }

    return std::nullopt;
}
vector<Artist> ArtistRepository::getAll()
{
    return artists;
}
