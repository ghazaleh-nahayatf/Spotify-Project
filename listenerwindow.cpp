#include "listenerwindow.h"
#include "ui_listenerwindow.h"
#include "spotifyexception.h"
#include "createplaylistwindow.h"
#include "editprofilewindow.h"
#include "loginwindow.h"
#include<QMessageBox>
#include<QDialog>

ListenerWindow::ListenerWindow(const Account &account,
                           EntryService &entryService,
                           ArtistService &artistService,
                           ListenerService& listenerService,
                           QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ListenerWindow),
    currentAccount(account),
    entryService(entryService),
    artistService(artistService),
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

    QString photoPath =
        QString::fromStdString(
            currentAccount.getProfilePhotoPath());

    if(!photoPath.isEmpty())
    {
        ui->profilePhotoLabel->setPixmap(
            QPixmap(photoPath).scaled(
                ui->profilePhotoLabel->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
    }
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
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a song.");

        return;
    }

    if(ui->playlistListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Select a playlist.");

        return;
    }

    int trackId =
        ui->songsListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    int playlistId =
        ui->playlistListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    try
    {
        listenerService.addSongToPlaylist(
            playlistId,
            trackId);

        QMessageBox::information(
            this,
            "Success",
            "Song added to playlist.");

        loadPlaylistSongs(playlistId);
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(
            this,
            "Error",
            ex.what());
    }
}


void ListenerWindow::on_removeFromPlaylistButton_clicked()
{
    if(ui->playlistListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please select a playlist.");

        return;
    }

    if(ui->playlistSongsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please select a song.");

        return;
    }

    int playlistId =
        ui->playlistListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    int trackId =
        ui->playlistSongsListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    try
    {
        listenerService.removeSongFromPlaylist(
            playlistId,
            trackId);

        loadPlaylistSongs(playlistId);

        QMessageBox::information(
            this,
            "Success",
            "Song removed from playlist.");
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(
            this,
            "Error",
            ex.what());
    }
}


void ListenerWindow::on_renamePlaylistButton_clicked()
{
    if(ui->playlistListWidget->currentRow() == -1)
    {
        QMessageBox::warning(
            this,
            "Error",
            "Please select a playlist.");

        return;
    }

    int playlistId =
        ui->playlistListWidget
            ->currentItem()
            ->data(Qt::UserRole)
            .toInt();

    Playlist playlist = listenerService.getPlaylist(playlistId);

    if(playlist.getPlaylistName() == "Favorites")
    {
        QMessageBox::warning(
            this,
            "Error",
            "Favorites playlist cannot be renamed.");

        return;
    }
    CreatePlaylistWindow dialog(
        listenerService,
        currentAccount.getAccountId(),
        playlist,
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        loadPlaylists();
    }
}


void ListenerWindow::on_editProfileButton_clicked()
{

    Listener listener = listenerService.getListener(currentAccount.getAccountId());

    EditProfileWindow dialog(
        listenerService,
        listener,
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        currentAccount = listenerService.getListener(currentAccount.getAccountId());

        QString photoPath =
            QString::fromStdString(
                currentAccount.getProfilePhotoPath());

        if(!photoPath.isEmpty())
        {
            ui->profilePhotoLabel->setPixmap(
                QPixmap(photoPath).scaled(
                    ui->profilePhotoLabel->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation));
        }

        ui->listenerPanelLabel->setText(
            QString::fromStdString(
                "Welcome, " +
                currentAccount.getFullName()));
    }
}


void ListenerWindow::on_deletePlaylistButton_clicked()
{
    if(ui->playlistListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a playlist.");

        return;
    }

    int playlistId = ui->playlistListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    Playlist playlist = listenerService.getPlaylist(playlistId);

    if(playlist.getPlaylistName() == "Favorites")
    {
        QMessageBox::warning(
            this,
            "Error",
            "Favorites playlist cannot be deleted.");

        return;
    }
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,
                                  "Delete Playlist",
                                  "Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    try
    {
        listenerService.deletePlaylist(playlistId);

        QMessageBox::information(this,
                                 "Success",
                                 "Playlist deleted successfully.");

        loadPlaylists();
        ui->playlistSongsListWidget->clear();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}


void ListenerWindow::on_logoutButton_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        this,
        "Log Out",
        "Are you sure you want to log out?",
        QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    LoginWindow *window = new LoginWindow(entryService,artistService, listenerService);

    window->show();

    close();

}


void ListenerWindow::on_searchLineEdit_textChanged(const QString &text)
{

    ui->songsListWidget->clear();

    vector<Song> songs = listenerService.getAllSongs();

    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        QString songName =
            QString::fromStdString(songs[i].getName());

        if(songName.contains(text, Qt::CaseInsensitive))
        {
            QListWidgetItem *item =
                new QListWidgetItem(songName);

            item->setData(
                Qt::UserRole,
                songs[i].getTrackId());

            ui->songsListWidget->addItem(item);
        }
    }
}


void ListenerWindow::on_recommendSongsButton_clicked()
{
    std::vector<Song> songs =listenerService.recommendSongs(currentAccount.getAccountId());
    ui->songsListWidget->clear();
    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        ui->songsListWidget->addItem(QString::fromStdString(songs[i].getName()));
    }
    if(songs.empty())
    {
        QMessageBox::information(
            this,
            "Recommendation",
            "No song recommendations found.");

        return;
    }
}


void ListenerWindow::on_showAllSongsButton_clicked()
{
    ui->songsListWidget->clear();

    vector<Song> songs = listenerService.getAllSongs();

    for (int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        ui->songsListWidget->addItem(
            QString::fromStdString(songs[i].getName()));
    }
}

