#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include <vector>
#include <optional>

#include "abstractrepository.h"
#include "playlist.h"
using namespace std;

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    vector<Playlist> playlists;
    int nextPlaylistId = 1;

public:
    PlaylistRepository();

    optional<int> save(const Playlist& entity) override;

    bool remove(int id) override;

    optional<Playlist> search(int id) override;

    vector<Playlist> getByListener(int listenerId);

    bool interSong(int playlistId, int trackId);

    bool removeSong(int playlistId, int trackId);
};
#endif // PLAYLISTREPOSITORY_H
