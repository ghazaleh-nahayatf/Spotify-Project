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
void Listener::showProfile()
{

}