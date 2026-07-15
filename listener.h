#ifndef LISTENER_H
#define LISTENER_H
#include "account.h"
#include <iostream>

using namespace std;

class Listener : public Account
{
public:
    Listener();
    Listener(string fullName,
           string userName,
           string biography,
           string ID,
           string role,
           string password);

    void showProfile() override;

    virtual ~Listener(){}
};

#endif // LISTENER_H
