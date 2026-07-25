#include "entryservice.h"
#include "spotifyexception.h"
#include "playlistrepository.h"
#include<QDebug>
EntryService::EntryService(
    ArtistRepository& artistRepository,
    ListenerRepository& listenerRepository,
    PlaylistRepository& playlistRepository)
    : artistRepository(artistRepository),
    listenerRepository(listenerRepository),
    playlistRepository(playlistRepository)
{
}
bool EntryService::registerArtist(const Artist& artist)
{
    if (artistRepository.searchByUserName(artist.getUserName()))
    {
        throw SpotifyException("Username already exists.");
    }

    if (listenerRepository.searchByUserName(artist.getUserName()))
    {
        throw SpotifyException("Username already exists.");
    }

    artistRepository.save(artist);

    return true;
}

bool EntryService::registerListener(const Listener& listener)
{
    if (artistRepository.searchByUserName(listener.getUserName()))
    {
        throw SpotifyException("Username already exists.");
    }

    if (listenerRepository.searchByUserName(listener.getUserName()))
    {
        throw SpotifyException("Username already exists.");
    }

    std::optional<int> listenerId = listenerRepository.save(listener);

    if (!listenerId.has_value())
    {
        throw SpotifyException("Could not create listener.");
    }
    if (playlistRepository.getFavoritePlaylistId(listenerId.value()) == -1)
    {
        Playlist favorite(
            "Favorites",
            0,
            listenerId.value());
        playlistRepository.save(favorite);
    }

    return true;
}
Account EntryService::login(const string& username, const string& password)
{
    std::optional<Account> account =
        artistRepository.searchByUserName(username);

    if (!account.has_value())
        account = listenerRepository.searchByUserName(username);

    if (!account.has_value())
        throw SpotifyException("User not found.");

    if (account->getPassword() != password)
        throw SpotifyException("Wrong password.");

    return account.value();
}








