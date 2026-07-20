#include "artist.h"

Artist::Artist()
    : Account()
{
}

Artist::Artist(string fullName,
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
string Artist :: getUserName()const
{
    return userName;
}
string Artist :: getPassword()const
{
    return password;
}
string Artist :: getFullName()const
{
    return fullName;
}
string Artist :: getRole()const
{
    return role;
}
string Artist :: getBiography()const
{
    return biography;
}
int Artist::getArtistId() const
{
    return ID;
}
void Artist::showProfile()
{

}