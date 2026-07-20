#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include <vector>
#include <optional>
#include <map>

#include "abstractrepository.h"
#include "playlist.h"
using namespace std;

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    vector<Playlist> playlists;
    map<int,vector<int>> playlistSongs;
    int nextPlaylistId = 1;

public:
    PlaylistRepository();

    optional<int> save(const Playlist& entity) override;

    bool remove(int id) override;

    optional<Playlist> search(int id) override;

    vector<Playlist> getByListener(int listenerId);

    bool addSong(int playlistId, int trackId);
    bool removeSong(int playlistId, int trackId);
};
#endif // PLAYLISTREPOSITORY_H
