#include "artist.h"

Artist::Artist()
    : Account()
{
}

Artist::Artist(string fullName,
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
void Artist::showProfile()
{

}