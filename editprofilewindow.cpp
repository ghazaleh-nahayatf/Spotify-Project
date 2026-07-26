#include "editprofilewindow.h"
#include "ui_editprofilewindow.h"
#include "spotifyexception.h"
#include "passwordstrength.h"
#include <QFileDialog>
#include <QPixmap>
#include<QMessageBox>

EditProfileWindow::EditProfileWindow(
    ArtistService &artistService,
    const Artist &artist,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditProfileWindow),
    artistService(&artistService),
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

    isArtist = true;
}
EditProfileWindow::EditProfileWindow(
   ListenerService &listenerService,
    const Listener &listener,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditProfileWindow),
    listenerService(&listenerService),
    currentListener(listener)
{
    ui->setupUi(this);

    ui->fullNameLineEdit->setText(
        QString::fromStdString(listener.getFullName()));

    ui->usernameLineEdit->setText(
        QString::fromStdString(listener.getUserName()));

    ui->biographyTextEdit->setPlainText(
        QString::fromStdString(listener.getBiography()));

    ui->passwordLineEdit->setText(
        QString::fromStdString(listener.getPassword()));

    if(!listener.getProfilePhotoPath().empty())
    {
        ui->photoLabel->setPixmap(
            QPixmap(
                QString::fromStdString(
                    listener.getProfilePhotoPath()))
                .scaled(
                    ui->photoLabel->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation));
    }

    isArtist = false;
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

    if(isArtist)
    {
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
            artistService->editProfile(currentArtist);

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
    else
    {
        currentListener.setFullName(
            fullName.toStdString());

        currentListener.setUserName(
            username.toStdString());

        currentListener.setBiography(
            biography.toStdString());

        currentListener.setPassword(
            password.toStdString());

        try
        {
            listenerService->editProfile(currentListener);

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

}


void EditProfileWindow::on_cancelButton_clicked()
{
    reject();
}

void EditProfileWindow::on_browsePhotoButton_clicked()
{
    QString path =
        QFileDialog::getOpenFileName(
            this,
            "Choose Profile Photo",
            "",
            "Images (*.png *.jpg *.jpeg)");

    if(path.isEmpty())
        return;

    if(isArtist)
    {
        currentArtist.setProfilePhotoPath(
            path.toStdString());
    }
    else
    {
        currentListener.setProfilePhotoPath(
            path.toStdString());
    }

    ui->photoLabel->setPixmap(
        QPixmap(path).scaled(
            ui->photoLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
}


void EditProfileWindow::on_passwordLineEdit_textChanged(const QString &text)
{
    ui->passwordStrengthLabel->setText(
        PasswordStrength::passStrength(text));
}

