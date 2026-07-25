#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "createalbumwindow.h"
#include "spotifyexception.h"

#include<QMessageBox>

ArtistWindow::ArtistWindow(const Account &account,
                           ArtistService &artistService,
                           QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ArtistWindow),
    currentAccount(account),
    artistService(artistService)
{
    ui->setupUi(this);

    ui->artistPanelLabel->setText(
        QString::fromStdString("Welcome, " + currentAccount.getFullName()));
    loadAlbums();
}
void ArtistWindow::on_createAlbumButton_clicked()
{
    CreateAlbumWindow dialog(
        artistService,
        currentAccount.getAccountId(),
        this);

    if(dialog.exec() == QDialog::Accepted)
    {
        loadAlbums();
    }
}
void ArtistWindow::loadAlbums()
{
    ui->listWidget->clear();

    std::vector<Album> albums = artistService.getAlbums(currentAccount.getAccountId());

    for(int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        QListWidgetItem *item = new QListWidgetItem(
            QString::fromStdString(albums[i].getAlbumName()));

        item->setData(Qt::UserRole, albums[i].getAlbumId());

        ui->listWidget->addItem(item);
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

