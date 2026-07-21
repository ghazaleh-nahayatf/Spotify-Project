#include "listenerfilemanger.h"
#include "listener.h"
#include "fileexception.h"

#include <fstream>
#include <sstream>

using namespace std;

void ListenerFileManager::save(const vector<Listener>& listeners)
{
    ofstream file("listeners.txt");

    if (!file.is_open())
    {
        throw FileException("Cannot open listeners.txt");
    }

    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        file << listeners[i].getListenerId() << '|'
             << listeners[i].getFullName() << '|'
             << listeners[i].getUserName() << '|'
             << listeners[i].getPassword() << '|'
             << listeners[i].getBiography() << '|'
             << listeners[i].getRole() << '|';

        const vector<int>& liked = listeners[i].getLikedSongs();

        for (int j = 0; j < static_cast<int>(liked.size()); j++)
        {
            file << liked[j];

            if (j != static_cast<int>(liked.size()) - 1)
                file << ",";
        }

        file << '\n';
    }

    file.close();
}
vector<Listener> ListenerFileManager::load()
{
    vector<Listener> listeners;

    ifstream file("listeners.txt");

    if (!file.is_open())
        return listeners;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string fullName;
        string userName;
        string password;
        string role;
        string biography;
        string ID;
        string likedSongs;

        getline(ss, ID, '|');
        getline(ss, fullName, '|');
        getline(ss, userName, '|');
        getline(ss, password, '|');
        getline(ss, biography, '|');
        getline(ss, role, '|');
        getline(ss, likedSongs, '|');

        Listener listener(
            fullName,
            userName,
            biography,
            stoi(ID),
            role,
            password);

        stringstream likedStream(likedSongs);

        string id;

        while (getline(likedStream, id, ','))
        {
            if (!id.empty())
                listener.updateLiked(stoi(id), true);
        }

        listeners.push_back(listener);
    }

    file.close();

    return listeners;
}