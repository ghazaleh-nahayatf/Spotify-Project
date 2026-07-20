#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

using namespace std;

class Account
{
protected:
    string fullName;
    string userName;
    string biography;
    int ID;
    string role;
    string password;
public:
    Account();
    Account(string fullName,
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
    int getAccountId() const;

    void setAccountId(int newId);
    void setBiography(const string& biography);

    virtual void showProfile();
    virtual ~Account(){}

};

#endif // ACCOUNT_H
