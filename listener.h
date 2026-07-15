#ifndef LISTENER_H
#define LISTENER_H
#include "account.h"

using namespace std;

class Listener : public Account
{
public:
    Listener();
    Listener(string fullName,
           string userName,
           string biography,
           int ID,
           string role,
           string password);

    void showProfile() override;

    virtual ~Listener(){}
};

#endif // LISTENER_H
