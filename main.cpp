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

   /* std::optional<Account> artist =
        artistRepository.searchByUserName("abc");

    std::optional<Account> listener =
        listenerRepository.searchByUserName("abc");
    */
    EntryService entryService(
        artistRepository,
        listenerRepository,
        playlistRepository);

    LoginWindow window(entryService);
    window.show();

    return a.exec();
}