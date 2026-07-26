#include "playlistfilemanger.h"
#include "fileexception.h"
#include "PlaylistData.h"
#include <fstream>
#include <sstream>

using namespace std;

void PlaylistFileManager::save( const vector<Playlist>& playlists, const map<int,vector<int>>& playlistSongs)
{
    ofstream file("C:/Users/Ghazaleh/Desktop/c++/Advanced/AP/project 2/files/playlists.txt");

    if (!file.is_open())
    {
        throw FileException("Cannot open playlists.txt");
    }

    for (int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        file << playlists[i].getPlaylistName() << '|'
             << playlists[i].getPlaylistId() << '|'
             << playlists[i].getListenerId() << '|';

        for (int j = 0; j < static_cast<int>( playlistSongs.at(playlists[i].getPlaylistId()).size()); j++)
        {
            file << playlistSongs.at(playlists[i].getPlaylistId())[j];

            if (j != static_cast<int>( playlistSongs.at(playlists[i].getPlaylistId()).size()) - 1)
            {
                file << ",";
            }
        }

        file << '\n';
    }

    file.close();
}
PlaylistData  PlaylistFileManager::load()
{
    PlaylistData data;

    ifstream file("C:/Users/Ghazaleh/Desktop/c++/Advanced/AP/project 2/files/playlists.txt");

    if (!file.is_open())
        return data;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string playlistName;
        string playlistId;
        string listenerId;
        string songIds;

        getline(ss, playlistName, '|');
        getline(ss, playlistId, '|');
        getline(ss, listenerId, '|');
        getline(ss, songIds);


        Playlist playlist(
            playlistName,
            stoi(playlistId),
            stoi(listenerId));

        data.playlists.push_back(playlist);

        stringstream songStream(songIds);

        string id;

        while(getline(songStream,id,','))
        {
            if(!id.empty())
            {
                data.playlistSongs[ playlist.getPlaylistId()].push_back(stoi(id));
            }
        }
    }

    return data;
}