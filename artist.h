#ifndef ARTIST_H
#define ARTIST_H
#include "account.h"
#include <iostream>

using namespace std;

class Artist : public Account
{
public:
    Artist();
    Artist(string fullName,
           string userName,
           string biography,
           int ID,
           string role,
           string password);

    void showProfile() override;

    string getUserName() const;
    string getPassword() const;
    string getFullName() const;
    string getuserName() const;
    string getRole() const;
    string getBiography() const;
    int getArtistId() const;

    void setArtistId(int newId);

    virtual ~Artist(){}
};

#endif // ARTIST_H
