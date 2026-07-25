#include <QApplication>

#include "loginwindow.h"

#include "artistrepository.h"
#include "listenerrepository.h"
#include "playlistrepository.h"

#include "entryservice.h"
#include "artistservice.h"
#include "listenerservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ArtistRepository artistRepository;
    ListenerRepository listenerRepository;
    PlaylistRepository playlistRepository;
    SongRepository songRepository;
    AlbumRepository albumRepository;

    ArtistService artistService(
        artistRepository,
        songRepository,
        albumRepository,
        playlistRepository,
        listenerRepository);

    ListenerService listenerService(
        listenerRepository,
        playlistRepository,
        songRepository,
        artistRepository);

    EntryService entryService(
        artistRepository,
        listenerRepository,
        playlistRepository);

    LoginWindow window(entryService, artistService,listenerService);

    window.show();

    return a.exec();
}