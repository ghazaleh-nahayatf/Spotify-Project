#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "createalbumwindow.h"

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
        ui->listWidget->addItem(
            QString::fromStdString(albums[i].getAlbumName()));
    }
}
ArtistWindow::~ArtistWindow()
{
    delete ui;
}
