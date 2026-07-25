#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QWidget>
#include "account.h"
#include "artistservice.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListWidgetItem>
#include <QListWidget>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QWidget
{
    Q_OBJECT

public:
   explicit ArtistWindow(const Account &account,
                          ArtistService &artistService,
                          QWidget *parent = nullptr);
    ~ArtistWindow();

private slots:
    void on_createAlbumButton_clicked();

    void on_deleteAlbumButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_createSongButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::ArtistWindow *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    Account currentAccount;
    ArtistService &artistService;
    void loadAlbums();
    void loadSongs(int albumId);
    void loadSingles();
};

#endif // ARTISTWINDOW_H
