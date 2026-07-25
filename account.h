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
    string profilePhotoPath;
public:
    Account();
    Account(string fullName,
            string userName,
            string biography,
            int ID,
            string role,
            string password,
            string profilePhotoPath = "");

    string getUserName() const;
    string getPassword() const;
    string getFullName() const;
    string getRole() const;
    string getBiography() const;
    int getAccountId() const;
    string getProfilePhotoPath() const;

    void setProfilePhotoPath(const string& path);
    void setAccountId(int newId);
    void setBiography(const string& biography);

    virtual void showProfile();
    virtual ~Account(){}

};

#endif // ACCOUNT_H
