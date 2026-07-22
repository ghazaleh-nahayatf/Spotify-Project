#include "listenerrepository.h"
#include "listenerfilemanger.h"

ListenerRepository::ListenerRepository()
{
    listeners = ListenerFileManager::load();

    nextListenerId = 1;

    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getListenerId() >= nextListenerId)
            nextListenerId = listeners[i].getListenerId() + 1;
    }
}

std::optional<int> ListenerRepository::save(const Listener& entity)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getListenerId() == entity.getListenerId())
        {
            listeners[i] = entity;
            ListenerFileManager::save(listeners);
            return listeners[i].getListenerId();
        }
    }

    Listener newListener = entity;
    newListener.setListenerId(nextListenerId++);

    listeners.push_back(newListener);

    ListenerFileManager::save(listeners);

    return newListener.getListenerId();
}

bool ListenerRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getListenerId() == id)
        {
            listeners.erase(listeners.begin() + i);

            ListenerFileManager::save(listeners);

            return true;
        }
    }

    return false;
}

std::optional<Listener> ListenerRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getListenerId() == id)
            return listeners[i];
    }

    return std::nullopt;
}

std::optional<Account> ListenerRepository::searchByUserName(
    const std::string& username)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getUserName() == username)
            return listeners[i];
    }

    return std::nullopt;
}
bool ListenerRepository::updateLiked(int listenerId,int trackId,bool liked)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].getListenerId() == listenerId)
        {
            listeners[i].updateLiked(trackId, liked);

            ListenerFileManager::save(listeners);

            return true;
        }
    }

    return false;
}
bool ListenerRepository::isLiked(int listenerId,int trackId)
{
    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if(listeners[i].getListenerId() == listenerId)
            return listeners[i].isLiked(trackId);
    }
    return false;
}
bool ListenerRepository::removeLikedSongFromAllListeners(int trackId)
{
    bool removed = false;

    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        if (listeners[i].isLiked(trackId))
        {
            listeners[i].updateLiked(trackId, false);
            removed = true;
        }
    }

    if (removed)
    {
        ListenerFileManager::save(listeners);
    }

    return removed;
}