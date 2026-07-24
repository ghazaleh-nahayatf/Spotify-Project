#include <QApplication>

#include "loginwindow.h"

#include "artistrepository.h"
#include "listenerrepository.h"
#include "playlistrepository.h"

#include "entryservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ArtistRepository artistRepository;
    ListenerRepository listenerRepository;
    PlaylistRepository playlistRepository;

    EntryService entryService(
        artistRepository,
        listenerRepository,
        playlistRepository);

    LoginWindow window(entryService);
    window.show();

    return a.exec();
}