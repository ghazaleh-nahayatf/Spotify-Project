#include <QApplication>

#include "loginwindow.h"

#include "artistrepository.h"
#include "listenerrepository.h"
#include "playlistrepository.h"

#include "entryservice.h"
#include "artistservice.h"

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

    EntryService entryService(
        artistRepository,
        listenerRepository,
        playlistRepository);

    LoginWindow window(entryService, artistService);

    window.show();

    return a.exec();
}