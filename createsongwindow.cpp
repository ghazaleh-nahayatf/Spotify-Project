#include "createsongwindow.h"
#include "ui_createsongwindow.h"
#include "spotifyexception.h"
#include<QMessageBox>
#include <QFileDialog>

CreateSongWindow::CreateSongWindow(
    ArtistService &artistService,
    int artistId,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateSongWindow),
    artistService(artistService),
    artistId(artistId)
{
    ui->setupUi(this);

    loadAlbums();
}
void CreateSongWindow::loadAlbums()
{
    ui->albumComboBox->clear();

    ui->albumComboBox->addItem("Singles", 0);

    vector<Album> albums =
        artistService.getAlbums(artistId);

    for(int i = 0; i < static_cast<int>(albums.size()); i++)
    {
        ui->albumComboBox->addItem(
            QString::fromStdString(albums[i].getAlbumName()),
            albums[i].getAlbumId());
    }
}
CreateSongWindow::~CreateSongWindow()
{
    delete ui;
}

void CreateSongWindow::on_cancelButton_clicked()
{
    reject();
}


void CreateSongWindow::on_createButton_clicked()
{
    QString songName = ui->songNameLineEdit->text().trimmed();
    int releaseYear = ui->releaseYearSpinBox->value();
    QString genre = ui->genreComboBox->currentText();
    QString filePath = ui->filePathLineEdit->text();
    int albumId = ui->albumComboBox->currentData().toInt();

    if(songName.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter song name.");
        return;
    }

    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please choose a song file.");
        return;
    }

    try
    {
        Song song(
            songName.toStdString(),
            releaseYear,
            genre.toStdString(),
            filePath.toStdString(),
            0,
            artistId,
            albumId);

        artistService.createSong(song);

        QMessageBox::information(this, "Success", "Song created successfully.");

        accept();
    }
    catch(const SpotifyException &ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
    }
}


void CreateSongWindow::on_browseButton_clicked()
{
    QString filePath =
        QFileDialog::getOpenFileName(
            this,
            "Select Song",
            "",
            "Audio Files (*.mp3 *.wav *.ogg)");

    if(filePath.isEmpty())
        return;

    ui->filePathLineEdit->setText(filePath);
}

