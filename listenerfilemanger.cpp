#include "listenerfilemanger.h"
#include "listener.h"
#include <fstream>
#include <sstream>

using namespace std;

void ListenerFileManager::save(const vector<Listener>& listeners)
{
    ofstream file("listeners.txt");

    if (!file.is_open())
        throw runtime_error("Cannot open listeners.txt");

    for (int i = 0; i < static_cast<int>(listeners.size()); i++)
    {
        file << listeners[i].getListenerId() << '|'
             << listeners[i].getFullName() << '|'
             << listeners[i].getUserName() << '|'
             << listeners[i].getPassword() << '|'
             << listeners[i].getBiography() << '|'
             << listeners[i].getRole()
             << '\n';
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

        getline(ss, ID, '|');
        getline(ss, fullName, '|');
        getline(ss, userName, '|');
        getline(ss, password, '|');
        getline(ss, biography, '|');
        getline(ss, role, '|');

        Listener listener(
            fullName,
            userName,
            biography,
            stoi(ID),
            role,
            password);

        listeners.push_back(listener);
    }

    file.close();

    return listeners;
}