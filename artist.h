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
           string ID,
           string role,
           string password);

    void showProfile() override;

    virtual ~Artist(){}
};

#endif // ARTIST_H
