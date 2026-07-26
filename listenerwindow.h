#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>
#include "listenerservice.h"
#include "entryservice.h"
#include "artistservice.h"

namespace Ui {
class ListenerWindow;
}

class ListenerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListenerWindow(const Account &account,
                            EntryService &entryService,
                            ArtistService& artistService,
                            ListenerService &listenerService,
                            QWidget *parent = nullptr);
    ~ListenerWindow();
    void loadPlaylistSongs(int playlistId);

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_likeButton_clicked();

    void on_playlistListWidget_itemClicked(QListWidgetItem *item);

    void on_createPlaylistButton_clicked();

    void on_addToPlaylistButton__clicked();

    void on_removeFromPlaylistButton_clicked();

    void on_renamePlaylistButton_clicked();

    void on_editProfileButton_clicked();

    void on_deletePlaylistButton_clicked();

    void on_logoutButton_clicked();

    void on_searchLineEdit_textChanged(const QString &arg1);

    void on_recommendSongsButton_clicked();

    void on_showAllSongsButton_clicked();

private:
    Ui::ListenerWindow *ui;

    Account currentAccount;

    EntryService& entryService;
    ArtistService& artistService;
    ListenerService& listenerService;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    void loadSongs();
    void loadPlaylists();
};

#endif // LISTENERWINDOW_H
