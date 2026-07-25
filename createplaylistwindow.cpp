#include "createplaylistwindow.h"
#include "ui_createplaylistwindow.h"
#include "spotifyexception.h"
#include<QMessageBox>

CreatePlaylistWindow::CreatePlaylistWindow(
    ListenerService &listenerService,
    int listenerId,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreatePlaylistWindow),
    listenerService(listenerService),
    listenerId(listenerId)
{
    ui->setupUi(this);
}
CreatePlaylistWindow::~CreatePlaylistWindow()
{
    delete ui;
}

void CreatePlaylistWindow::on_createButton_clicked()
{
    QString name =
        ui->playlistNameLineEdit->text();

    if(name.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Error",
            "Enter playlist name.");

        return;
    }

    Playlist playlist;

    playlist.setPlaylistName(
        name.toStdString());

    playlist.setListenerId(listenerId);

    try
    {
        listenerService.createPlaylist(
            playlist);

        accept();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(
            this,
            "Error",
            ex.what());
    }
}


void CreatePlaylistWindow::on_cancelButton_clicked()
{
    reject();
}

