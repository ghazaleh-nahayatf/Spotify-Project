#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<iostream>

using namespace std;

class Playlist
{
private:
    string playlistName;
    int playlistId;
    int listenerId;
public:
    Playlist();
    Playlist(const string& playlistName,
             int playlistId,
             int listenerId);
    int getPlaylistId();
    virtual ~Playlist(){}
};

#endif // PLAYLIST_H
