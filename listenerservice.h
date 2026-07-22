#ifndef LISTENERSERVICE_H
#define LISTENERSERVICE_H
#include "listenerrepository.h"
#include "playlistrepository.h"
#include "songrepository.h"
#include "artistrepository.h"
#include "artist.h"

class ListenerService
{
private:
    ListenerRepository& listenerRepository;
    PlaylistRepository& playlistRepository;
    SongRepository& songRepository;
    ArtistRepository& artistRepository;

public:
    ListenerService(ListenerRepository& listenerRepository,
                    PlaylistRepository& playlistRepository,
                    SongRepository& songRepository,
                    ArtistRepository& artistRepository);

    bool createPlaylist(const Playlist& playlist);

    bool editPlaylist(const Playlist& playlist);

    bool deletePlaylist(int playlistId);

    bool addSongToPlaylist(int playlistId, int trackId);

    bool removeSongFromPlaylist(int playlistId, int trackId);

    bool likeSong(int listenerId, int trackId);

    bool unlikeSong(int listenerId, int trackId);

    vector<Playlist> getPlaylists(int listenerId);

    vector<Artist> getArtists();

    vector<Song> getPlaylistSongs(int playlistId);

    bool deleteListener(int listenerId);
};

#endif // LISTENERSERVICE_H
