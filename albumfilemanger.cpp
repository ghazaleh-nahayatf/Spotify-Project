#include "albumfilemanger.h"
#include <fstream>
#include <sstream>

using namespace std;

void AlbumFileManager::save(const vector<Album>& albums)
{
    ofstream file("albums.txt");

    if (!file.is_open())
        throw runtime_error("Cannot open albums.txt");

    for (int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        file << albums[i].getAlbumName() << '|'
             << albums[i].getAlbumId() << '|'
             << albums[i].getArtistId()
             << '\n';
    }

    file.close();
}
vector<Album> AlbumFileManager::load()
{
    vector<Album> albums;

    ifstream file("albums.txt");

    if (!file.is_open())
        return albums;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string albumName;
        string artistId;
        string albumId;

        getline(ss, albumName, '|');
        getline(ss, albumId, '|');
        getline(ss, artistId, '|');

        Album album(
            albumName,
            stoi(albumId),
            stoi(artistId));

        albums.push_back(album);
    }

    file.close();

    return albums;
}