#include "editprofilewindow.h"
#include "ui_editprofilewindow.h"
#include "spotifyexception.h"
#include <QFileDialog>
#include <QPixmap>
#include<QMessageBox>

EditProfileWindow::EditProfileWindow(
    ArtistService &artistService,
    const Artist &artist,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditProfileWindow),
    artistService(artistService),
    currentArtist(artist)
{
    ui->setupUi(this);

    ui->fullNameLineEdit->setText(
        QString::fromStdString(artist.getFullName()));

    ui->usernameLineEdit->setText(
        QString::fromStdString(artist.getUserName()));

    ui->biographyTextEdit->setPlainText(
        QString::fromStdString(artist.getBiography()));

    ui->passwordLineEdit->setText(
        QString::fromStdString(artist.getPassword()));

    if(!artist.getProfilePhotoPath().empty())
    {
        ui->photoLabel->setPixmap(
            QPixmap(
                QString::fromStdString(
                    artist.getProfilePhotoPath()))
                .scaled(
                    ui->photoLabel->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation));
    }
}

EditProfileWindow::~EditProfileWindow()
{
    delete ui;
}

void EditProfileWindow::on_saveButton_clicked()
{
    QString fullName = ui->fullNameLineEdit->text().trimmed();

    QString username =ui->usernameLineEdit->text().trimmed();

    QString biography = ui->biographyTextEdit->toPlainText();

    QString password = ui->passwordLineEdit->text();

    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    if(fullName.isEmpty() ||
        username.isEmpty() ||
        password.isEmpty())
    {
        QMessageBox::warning(this,
                             "Error",
                             "Please fill all fields.");

        return;
    }

    if(password != confirmPassword)
    {
        QMessageBox::warning(this,
                             "Error",
                             "Passwords do not match.");

        return;
    }
    currentArtist.setFullName(
        fullName.toStdString());

    currentArtist.setUserName(
        username.toStdString());

    currentArtist.setBiography(
        biography.toStdString());

    currentArtist.setPassword(
        password.toStdString());

    try
    {
        artistService.editProfile(currentArtist);

        QMessageBox::information(this,
                                 "Success",
                                 "Profile updated successfully.");

        accept();
    }
    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Error",
                             ex.what());
    }
}


void EditProfileWindow::on_cancelButton_clicked()
{
    reject();
}


void EditProfileWindow::on_browseButton_clicked()
{
    QString path =
        QFileDialog::getOpenFileName(
            this,
            "Choose Profile Photo",
            "",
            "Images (*.png *.jpg *.jpeg)");

    if(path.isEmpty())
        return;

    currentArtist.setProfilePhotoPath(
        path.toStdString());

    ui->photoLabel->setPixmap(
        QPixmap(path).scaled(
            ui->photoLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
}

