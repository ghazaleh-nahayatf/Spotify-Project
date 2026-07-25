#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "loginwindow.h"
#include "createalbumwindow.h"
#include "spotifyexception.h"
#include "createsongwindow.h"
#include "editprofilewindow.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QPixmap>
#include <QUrl>

ArtistWindow::ArtistWindow(const Account &account,
                           EntryService &entryService,
                           ArtistService &artistService,
                           QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ArtistWindow),
    currentAccount(account),
    entryService(entryService),
    artistService(artistService)
{
    ui->setupUi(this);

    ui->artistPanelLabel->setText(
        QString::fromStdString("Welcome, " + currentAccount.getFullName()));
    loadAlbums();
    audioOutput = new QAudioOutput(this);

    player = new QMediaPlayer(this);

    player->setAudioOutput(audioOutput);

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
void ArtistWindow::on_createAlbumButton_clicked()
{
    CreateAlbumWindow dialog(
        artistService,
        currentAccount.getAccountId(),
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        if(ui->listWidget->currentItem() != nullptr)
        {
            on_listWidget_itemClicked(ui->listWidget->currentItem());
        }
    }
}
void ArtistWindow::loadAlbums()
{
    ui->listWidget->clear();

    QListWidgetItem *singlesItem =
        new QListWidgetItem("🎵 Singles");

    singlesItem->setData(Qt::UserRole, -1);

    ui->listWidget->addItem(singlesItem);

    std::vector<Album> albums = artistService.getAlbums(currentAccount.getAccountId());

    for(int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(
            QString::fromStdString(albums[i].getAlbumName()));

        item->setData(Qt::UserRole, albums[i].getAlbumId());

        ui->listWidget->addItem(item);
    }
}
void ArtistWindow::loadSingles()
{
    ui->songsListWidget->clear();

    vector<Song> songs =
        artistService.getSingles(currentAccount.getAccountId());

    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(songs[i].getName()));

        item->setData(Qt::UserRole,
                      songs[i].getTrackId());

        ui->songsListWidget->addItem(item);
    }
}
ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::on_deleteAlbumButton_clicked()
{
    if(ui->listWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select an album.");

        return;
    }
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this,
                                  "Delete Album",
                                  "Are you sure?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    QListWidgetItem *item = ui->listWidget->currentItem();

    int albumId = item->data(Qt::UserRole).toInt();

    try
    {
        artistService.deleteAlbum(albumId);

        QMessageBox::information(this,
                                 "Success",
                                 "Album deleted successfully.");

        loadAlbums();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}

void ArtistWindow::loadSongs(int albumId)
{
    ui->songsListWidget->clear();

    vector<Song> songs =
        artistService.getAlbumSongs(albumId);

    for(int i = 0; i < static_cast<int>(songs.size()); i++)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(songs[i].getName()));

        item->setData(Qt::UserRole,
                      songs[i].getTrackId());

        ui->songsListWidget->addItem(item);
    }
}
void ArtistWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int albumId = item->data(Qt::UserRole).toInt();

    if(albumId == -1)
    {
        loadSingles();
    }
    else
    {
        loadSongs(albumId);
    }
}


void ArtistWindow::on_createSongButton_clicked()
{
    CreateSongWindow dialog(
        artistService,
        currentAccount.getAccountId(),
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        if(ui->listWidget->currentItem() != nullptr)
        {
            on_listWidget_itemClicked(
                ui->listWidget->currentItem());
        }
    }
}


void ArtistWindow::on_playButton_clicked()
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
        Song song = artistService.getSong(trackId);

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


void ArtistWindow::on_pauseButton_clicked()
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


void ArtistWindow::on_stopButton_clicked()
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


void ArtistWindow::on_editSongButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a song.");

        return;
    }

    int trackId =
        ui->songsListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    Song song =
        artistService.getSong(trackId);

    CreateSongWindow dialog(
        artistService,
        currentAccount.getAccountId(),
        song,
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        on_listWidget_itemClicked(
            ui->listWidget->currentItem());
    }
}


void ArtistWindow::on_editAlbumButton_clicked()
{
    if(ui->listWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select an album.");

        return;
    }

    int albumId =
        ui->listWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    if(albumId == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Singles cannot be edited.");

        return;
    }

    Album album = artistService.getAlbum(albumId);

    CreateAlbumWindow dialog(
        artistService,
        currentAccount.getAccountId(),
        album,
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        loadAlbums();
    }
}


void ArtistWindow::on_deleteSongButton_clicked()
{
    if(ui->songsListWidget->currentRow() == -1)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please select a song.");
        return;
    }

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        this,
        "Delete Song",
        "Are you sure?",
        QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    int trackId =
        ui->songsListWidget->currentItem()
            ->data(Qt::UserRole).toInt();

    try
    {
        artistService.deleteSong(trackId);

        QMessageBox::information(this,
                                 "Success",
                                 "Song deleted successfully.");

        if(ui->listWidget->currentItem() != nullptr)
        {
            on_listWidget_itemClicked(
                ui->listWidget->currentItem());
        }
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}


void ArtistWindow::on_editProfileButton_clicked()
{
        Artist artist =
            artistService.getArtist(currentAccount.getAccountId());

        EditProfileWindow dialog(
            artistService,
            artist,
            this);

        if(dialog.exec() == QDialog::Accepted)
        {
            currentAccount = artistService.getArtist(currentAccount.getAccountId());

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

            ui->artistPanelLabel->setText(
                QString::fromStdString(
                    "Welcome, " +
                    currentAccount.getFullName()));
        }
}


void ArtistWindow::on_logoutButton_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(
        this,
        "Log Out",
        "Are you sure you want to log out?",
        QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    LoginWindow *window =
        new LoginWindow(entryService,artistService);

    window->show();

    close();
}

