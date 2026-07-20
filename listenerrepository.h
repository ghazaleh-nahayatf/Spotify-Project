#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H
#include "accountrepository.h"
#include "listener.h"
#include <vector>
#include <optional>

class ListenerRepository : public AccountRepository
{
private:
    std::vector<Listener> listeners;
    int nextListenerId = 1;

public:
    ListenerRepository();

    std::optional<int> save(const Listener& entity);

    bool remove(int id);

    std::optional<Listener> search(int id);

    std::optional<Account> searchByUserName(
        const std::string& username) override;
};

#endif // LISTENERREPOSITORY_H
