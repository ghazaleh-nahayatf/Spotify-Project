#include "createalbumwindow.h"
#include "ui_createalbumwindow.h"
#include <QMessageBox>
#include "spotifyexception.h"
#include "album.h"

CreateAlbumWindow::CreateAlbumWindow(ArtistService &artistService,
                                     int artistId,
                                     QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateAlbumWindow),
    artistService(artistService),
    artistId(artistId)
{
    ui->setupUi(this);
}
CreateAlbumWindow::CreateAlbumWindow(
    ArtistService& artistService,
    int artistId,
    const Album& album,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateAlbumWindow),
    artistService(artistService),
    artistId(artistId),
    currentAlbum(album),
    editMode(true)
{
    ui->setupUi(this);

    ui->albumNameLineEdit->setText(
        QString::fromStdString(album.getAlbumName()));

    ui->createAlbumButton->setText("Save");
}
CreateAlbumWindow::~CreateAlbumWindow()
{
    delete ui;
}

void CreateAlbumWindow::on_cancelButton_clicked()
{
    reject();
}


void CreateAlbumWindow::on_createAlbumButton_clicked()
{
    QString albumName = ui->albumNameLineEdit->text().trimmed();

    if(albumName.isEmpty())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please enter album name.");

        return;
    }

    try
    {
        Album album(
            albumName.toStdString(),
            0,
            artistId);

        if(editMode)
        {
            album.setAlbumId(currentAlbum.getAlbumId());

            artistService.editAlbum(album);
        }
        else
        {
            artistService.createAlbum(album);
        }

        QMessageBox::information(this,
                                 "Success",
                                 "Album saved successfully.");

        accept();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}

