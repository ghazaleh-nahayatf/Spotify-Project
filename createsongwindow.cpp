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
CreateSongWindow::CreateSongWindow(
    ArtistService& artistService,
    int artistId,
    const Song& song,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateSongWindow),
    artistService(artistService),
    artistId(artistId),
    currentSong(song),
    editMode(true)
{
    ui->setupUi(this);

    loadAlbums();

    ui->songNameLineEdit->setText(
        QString::fromStdString(song.getName()));

    ui->releaseYearSpinBox->setValue(
        song.getReleaseYear());

    ui->genreComboBox->setCurrentText(
        QString::fromStdString(song.getGenre()));

    ui->filePathLineEdit->setText(
        QString::fromStdString(song.getFilePath()));

    ui->albumComboBox->setCurrentIndex(
        ui->albumComboBox->findData(song.getAlbumId()));

    ui->createButton->setText("Save");
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

        if(editMode)
        {
            song.setTrackId(currentSong.getTrackId());

            artistService.editSong(song);
        }
        else
        {
            artistService.createSong(song);
        }

        QMessageBox::information(this, "Success", "Song saved successfully.");

        accept();
    }
    catch(const SpotifyException &ex)
    {
        QMessageBox::warning(this, "Error", ex.what());
    }
}


void CreateSongWindow::on_browseButton_clicked()
{
    QString path =
        QFileDialog::getOpenFileName(
            this,
            "Choose Song",
            "",
            "Audio Files (*.mp3 *.wav *.flac *.ogg)");

    if(path.isEmpty())
        return;

    ui->filePathLineEdit->setText(path);
}


void CreateSongWindow::on_CreateSongWindow_accepted()
{

}

