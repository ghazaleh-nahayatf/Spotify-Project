#include "accountservice.h"
#include "spotifyexception.h"

AccountService::AccountService(
    ArtistRepository& artistRepository,
    ListenerRepository& listenerRepository)
    : artistRepository(artistRepository),
    listenerRepository(listenerRepository)
{
}

bool AccountService::editArtist(const Artist& artist)
{
    if (!artistRepository.search(artist.getArtistId()).has_value())
        throw SpotifyException("Artist not found.");

    artistRepository.save(artist);

    return true;
}
bool AccountService::editListener(const Listener& listener)
{
    if (!listenerRepository.search(listener.getListenerId()).has_value())
        throw SpotifyException("Listener not found.");

    listenerRepository.save(listener);

    return true;
}
