#include "listener.h"

Listener::Listener()
    : Account()
{
}

Listener::Listener(string fullName,
               string userName,
               string biography,
               string ID,
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
void Listener::showProfile()
{

}