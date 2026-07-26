#ifndef CREATESONGWINDOW_H
#define CREATESONGWINDOW_H
#include "artistservice.h"
#include <QDialog>

namespace Ui {
class CreateSongWindow;
}

class CreateSongWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSongWindow(
        ArtistService &artistService,
        int artistId,
        QWidget *parent = nullptr);
    CreateSongWindow(ArtistService& artistService,
                     int artistId,
                     const Song& song,
                     QWidget *parent = nullptr);
    ~CreateSongWindow();

private slots:
    void on_cancelButton_clicked();

    void on_createButton_clicked();

    void on_browseButton_clicked();

private:
    Ui::CreateSongWindow *ui;

    ArtistService &artistService;

    int artistId;

    void loadAlbums();

    Song currentSong;

     bool editMode = false;
     Artist currentArtist;

};

#endif // CREATESONGWINDOW_H
