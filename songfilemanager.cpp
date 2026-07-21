#include "songfilemanager.h"
#include "fileexception.h"
#include <fstream>
#include <sstream>

using namespace std;

void SongFileManager::save(const vector<Song>& songs)
{
    ofstream file("songs.txt");

    if (!file.is_open())
    {
        throw FileException("Cannot open songs.txt");
    }

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        file << songs[i].getTrackId() << '|'
             << songs[i].getName() << '|'
             << songs[i].getReleaseYear() << '|'
             << songs[i].getGenre() << '|'
             << songs[i].getFilePath() << '|'
             << songs[i].getArtistId() << '|'
             << songs[i].getAlbumId()
             << '\n';
    }

    file.close();
}
vector<Song> SongFileManager::load()
{
    vector<Song> songs;

    ifstream file("songs.txt");

    if (!file.is_open())
        return songs;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string trackId;
        string songName;
        string releaseYear;
        string genre;
        string filePath;
        string artistId;
        string albumId;

        getline(ss, trackId, '|');
        getline(ss, songName, '|');
        getline(ss, releaseYear, '|');
        getline(ss, genre, '|');
        getline(ss, filePath, '|');
        getline(ss, artistId, '|');
        getline(ss, albumId, '|');

        Song song(
            songName,
            stoi(releaseYear),
            genre,
            filePath,
            stoi(trackId),
            stoi(artistId),
            stoi(albumId));

        songs.push_back(song);
    }

    file.close();

    return songs;
}