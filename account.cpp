#include "account.h"

Account::Account(){}
Account::Account(string fullName, string userName, string biography,int ID, string role,string password)
    : fullName(fullName),
    userName(userName),
    biography(biography),
    ID(ID),
    role(role),
    password(password)
{
}

string Account :: getUserName()const
{
    return userName;
}
string Account :: getPassword()const
{
    return password;
}
void Account :: setBiography(const string& biography)
{
    this->biography=biography;
}