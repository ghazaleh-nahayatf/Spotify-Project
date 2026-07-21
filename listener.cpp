#include "listener.h"

Listener::Listener()
    : Account()
{
}

Listener::Listener(string fullName,
               string userName,
               string biography,
               int ID,
               string role,
               string password)
    : Account(fullName,
              userName,
              biography,
              ID,
              role,
              password)
{
}
string Listener :: getUserName()const
{
    return userName;
}
string Listener :: getPassword()const
{
    return password;
}
string Listener:: getFullName()const
{
    return fullName;
}
string Listener:: getRole()const
{
    return role;
}
string Listener :: getBiography()const
{
    return biography;
}
int Listener::getListenerId() const
{
    return ID;
}
void Listener::setListenerId(int newId)
{
    this->ID = newId;
}
bool Listener::isLiked(int trackId) const
{
    for (int i = 0; i < static_cast<int>(likedSongs.size()); i++)
    {
        if (likedSongs[i] == trackId)
            return true;
    }

    return false;
}
void Listener::updateLiked(int trackId, bool liked)
{
    if (liked)
    {
        for (int i = 0; i < static_cast<int>(likedSongs.size()); i++)
        {
            if (likedSongs[i] == trackId)
                return;
        }

        likedSongs.push_back(trackId);
    }
    else
    {
        for (int i = 0; i < static_cast<int>(likedSongs.size()); i++)
        {
            if (likedSongs[i] == trackId)
            {
                likedSongs.erase(likedSongs.begin() + i);
                return;
            }
        }
    }
}
const vector<int>& Listener::getLikedSongs() const
{
    return likedSongs;
}
void Listener::showProfile()
{

}