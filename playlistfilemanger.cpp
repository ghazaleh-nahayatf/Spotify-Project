#include "playlistfilemanger.h"

#include <fstream>
#include <sstream>

using namespace std;

void PlaylistFileManager::save(const vector<Playlist>& playlists)
{
    ofstream file("albums.txt");

    if (!file.is_open())
        throw runtime_error("Cannot open albums.txt");

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        file << playlists[i].getPlaylistName() << '|'
             << playlists[i].getPlaylistId() << '|'
             << playlists[i].getListenerId()
             << '\n';
    }

    file.close();
}
vector<Playlist> PlaylistFileManager::load()
{
    vector<Playlist> playlists;

    ifstream file("albums.txt");

    if (!file.is_open())
        return playlists;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string playlistName;
        string playlistId;
        string listenerId;

        getline(ss, playlistName, '|');
        getline(ss, playlistId, '|');
        getline(ss, listenerId, '|');

        Playlist album(
            playlistName,
            stoi(playlistId),
            stoi(listenerId));

        playlists.push_back(album);
    }

    file.close();

    return playlists;
}