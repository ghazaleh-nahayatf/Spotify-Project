#include "account.h"
#include<iostream>

Account::Account(){}
Account::Account(string fullName,
                 string userName,
                 string biography,
                 int ID,
                 string role,
                 string password,
                 string profilePhotoPath)
    : fullName(fullName),
    userName(userName),
    biography(biography),
    ID(ID),
    role(role),
    password(password),
    profilePhotoPath(profilePhotoPath)
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
string Account :: getFullName()const
{
    return fullName;
}
string Account :: getRole()const
{
    return role;
}
string Account :: getBiography()const
{
    return biography;
}
int Account::getAccountId() const
{
    return ID;
}
string Account::getProfilePhotoPath() const
{
    return profilePhotoPath;
}
void Account::setFullName(const string &name)
{
    fullName = name;
}

void Account::setUserName(const string &username)
{
    userName = username;
}

void Account::setPassword(const string &password)
{
    this->password = password;
}
void Account::setProfilePhotoPath(const string &path)
{
    profilePhotoPath = path;
}
void Account::setAccountId(int newId)
{
    this->ID = newId;
}
void Account :: setBiography(const string& biography)
{
    this->biography=biography;
}
void Account::showProfile()
{
    std::cout << "Name: " << fullName << endl;
    std::cout << "Username: " << userName << endl;
}