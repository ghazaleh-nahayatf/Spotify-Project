#ifndef ACCOUNTSERVICE_H
#define ACCOUNTSERVICE_H

#include "artistrepository.h"
#include "listenerrepository.h"

class AccountService
{
private:
    ArtistRepository& artistRepository;
    ListenerRepository& listenerRepository;

public:
    AccountService(ArtistRepository& artistRepository,
                   ListenerRepository& listenerRepository);

    bool editArtist(const Artist& artist);

    bool editListener(const Listener& listener);

};

#endif // ACCOUNTSERVICE_H
