#ifndef ENTRYSERVICE_H
#define ENTRYSERVICE_H
#include "artistrepository.h"
#include "listenerrepository.h"

class EntryService
{
private:
    ArtistRepository& artistRepository;
    ListenerRepository& listenerRepository;

public:
    EntryService(ArtistRepository& artistRepository,ListenerRepository& listenerRepository);

    bool registerArtist(const Artist& artist);
    bool registerListener(const Listener& listener);
    Account login(const std::string& username,const std::string& password);


};

#endif // ENTRYSERVICE_H
