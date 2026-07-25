#include "listenerwindow.h"
#include "ui_listenerwindow.h"
#include "spotifyexception.h"
#include "createplaylistwindow.h"
#include<QMessageBox>
#include<QDialog>

ListenerWindow::ListenerWindow(const Account &account,
                               EntryService &entryService,
                               ListenerService &listenerService,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ListenerWindow),
    currentAccount(account),
    entryService(entryService),
    listenerService(listenerService)
{
    ui->setupUi(this);

    ui->listenerPanelLabel->setText(
        QString::fromStdString(
            "Welcome, " +
            currentAccount.getFullName()));

    audioOutput = new QAudioOutput(this);

    player = new QMediaPlayer(this);

    player->setAudioOutput(audioOutput);

    loadSongs();

    loadPlaylists();
}
void ListenerWindow::loadSongs()
{
    ui->songsListWidget->clear();

    vector<Song> songs =
        listenerService.getAllSongs();

    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(
                    songs[i].getName()));

        item->setData(
            Qt::UserRole,
            songs[i].getTrackId());

        ui->songsListWidget->addItem(item);
    }
}
void ListenerWindow::loadPlaylists()
{
    ui->playlistListWidget->clear();

    vector<Playlist> playlists =
        listenerService.getPlaylists(
            currentAccount.getAccountId());

    for(int i = 0; i < static_cast<int>(playlists.size()); i++)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(
                    playlists[i].getPlaylistName()));

        item->setData(
            Qt::UserRole,
            playlists[i].getPlaylistId());

        ui->playlistListWidget->addItem(item);
    }
}
ListenerWindow::~ListenerWindow()
{
    delete ui;
}

void ListenerWindow::on_playButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a song.");
        return;
    }

    QListWidgetItem *item = ui->songsListWidget->currentItem();

    int trackId = item->data(Qt::UserRole).toInt();

    try
    {
        Song song = listenerService.getSong(trackId);

        player->setSource(
            QUrl::fromLocalFile(
                QString::fromStdString(song.getFilePath())));

        player->play();
    }
    catch(const SpotifyException &ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}


void ListenerWindow::on_pauseButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a song.");
        return;
    }
    player->pause();
}


void ListenerWindow::on_stopButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a song.");
        return;
    }
    player->stop();
}


void ListenerWindow::on_likeButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please select a song.");

        return;
    }

    int trackId =
        ui->songsListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    try
    {
        if(listenerService.isLiked(
                currentAccount.getAccountId(),
                trackId))
        {
            listenerService.unlikeSong(
                currentAccount.getAccountId(),
                trackId);

            QMessageBox::information(
                this,
                "Success",
                "Song removed from Favorites.");
        }
        else
        {
            listenerService.likeSong(
                currentAccount.getAccountId(),
                trackId);

            QMessageBox::information(
                this,
                "Success",
                "Song added to Favorites.");
        }

        loadPlaylists();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(
            this,
            "Error",
            ex.what());
    }
}


void ListenerWindow::on_playlistListWidget_itemClicked(QListWidgetItem *item)
{
    int playlistId = item->data(Qt::UserRole).toInt();

    loadPlaylistSongs(playlistId);
}
void ListenerWindow::loadPlaylistSongs(int playlistId)
{
    ui->playlistSongsListWidget->clear();

    vector<Song> songs =
        listenerService.getPlaylistSongs(playlistId);

    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(
                    songs[i].getName()));

        item->setData(
            Qt::UserRole,
            songs[i].getTrackId());

        ui->playlistSongsListWidget->addItem(item);
    }
}

void ListenerWindow::on_createPlaylistButton_clicked()
{
    CreatePlaylistWindow dialog(
        listenerService,
        currentAccount.getAccountId(),
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        loadPlaylists();
    }
}


void ListenerWindow::on_addToPlaylistButton__clicked()
{

}

