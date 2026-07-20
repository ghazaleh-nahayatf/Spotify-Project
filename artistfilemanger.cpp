#include "artistfilemanger.h"
#include "artist.h"
#include <fstream>
#include <sstream>

using namespace std;

void ArtistFileManager::save(const vector<Artist>& artists)
{
    ofstream file("artists.txt");

    if (!file.is_open())
        throw runtime_error("Cannot open artists.txt");

    for (int i = 0; i < static_cast<int>(artists.size()); i++)
    {
        file << artists[i].getArtistId() << '|'
             << artists[i].getFullName() << '|'
             << artists[i].getUserName() << '|'
             << artists[i].getPassword() << '|'
             << artists[i].getBiography() << '|'
             << artists[i].getRole()
             << '\n';
    }

    file.close();
}
vector<Artist> ArtistFileManager::load()
{
    vector<Artist> artists;

    ifstream file("artists.txt");

    if (!file.is_open())
        return artists;

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

        Artist artist(
            fullName,
            userName,
            biography,
            stoi(ID),
            role,
            password);

        artists.push_back(artist);
    }

    file.close();

    return artists;
}