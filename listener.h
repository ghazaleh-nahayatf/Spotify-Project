#ifndef LISTENER_H
#define LISTENER_H
#include "account.h"
#include<vector>

using namespace std;

class Listener : public Account
{
private:
    vector<int> likedSongs;
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

    void updateLiked(int trackId, bool liked);

    bool isLiked(int trackId) const;

    const vector<int>& getLikedSongs() const;

    void showProfile() override;

    virtual ~Listener(){}
};

#endif // LISTENER_H
