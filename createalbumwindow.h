#ifndef CREATEALBUMWINDOW_H
#define CREATEALBUMWINDOW_H

#include <QDialog>
#include "artistservice.h"

namespace Ui {
class CreateAlbumWindow;
}

class CreateAlbumWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAlbumWindow(ArtistService &artistService,int artistId, QWidget *parent = nullptr);
    CreateAlbumWindow(ArtistService& artistService,
                      int artistId,
                      const Album& album,
                      QWidget *parent = nullptr);
    ~CreateAlbumWindow();

private slots:
    void on_cancelButton_clicked();

    void on_createAlbumButton_clicked();

private:
    Ui::CreateAlbumWindow *ui;
    ArtistService &artistService;
    int artistId;
    Album currentAlbum;
    bool editMode;
};

#endif // CREATEALBUMWINDOW_H
