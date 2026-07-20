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

    string getUserName() const;
    string getPassword() const;
    string getFullName() const;
    string getuserName() const;
    string getRole() const;
    string getBiography() const;
    int getListenerId() const;

    void setListenerId(int newId);

    void showProfile() override;

    virtual ~Listener(){}
};

#endif // LISTENER_H
