#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#include"abstractrepository.h"
#include"song.h"
#include<vector>

using namespace std;

class SongRepository : public AbstractRepository <Song>
{
private:
    vector<Song> songs;
    int nextTrackId;

public:
    SongRepository();

    optional<int> save(const Song& entity) override;

    bool remove(int id) override;

    optional<Song> search(int id) override;

    vector<Song> singleSongs(int artistId);

    vector<Song> getByAlbum(int albumId);

    vector<Song> getByArtist(int artistId);

    vector<Song> getByPlaylist(int playlistId);

    vector<Song> getByLikedSongs(int listenerId);
};

#endif // SONGREPOSITORY_H
