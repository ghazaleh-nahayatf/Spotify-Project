#include "registerwindow.h"
#include "ui_registerwindow.h"

#include "loginwindow.h"
#include "spotifyexception.h"

#include <QMessageBox>

RegisterWindow::RegisterWindow(EntryService& entryService,
                               ArtistService& artistService,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::RegisterWindow),
    entryService(entryService),
    artistService(artistService)
{
    ui->setupUi(this);
}
void RegisterWindow::on_backButton_clicked()
{
    LoginWindow *window = new LoginWindow(entryService, artistService);

    window->show();

    close();
}
void RegisterWindow::on_registerButton_clicked()
{
    QString fullName = ui->nameLineEdit->text().trimmed();
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if(fullName.isEmpty() ||username.isEmpty() ||
        password.isEmpty() || confirmPassword.isEmpty())
    {
        QMessageBox::warning(this,"Error","Please fill all fields.");

        return;
    }

    if(password != confirmPassword)
    {
        QMessageBox::warning(this,"Error", "Passwords do not match.");

        ui->passwordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();
        ui->passwordLineEdit->setFocus();

        return;
    }

    try
    {
        if(ui->artistRadioButton->isChecked())
        {
            Artist artist(fullName.toStdString(), username.toStdString(),
                "", 1 ,"Artist", password.toStdString());

            entryService.registerArtist(artist);
        }
        else if(ui->listenerRadioButton->isChecked())
        {
            Listener listener(fullName.toStdString(), username.toStdString(),
                "", 1 ,"Listener", password.toStdString());

            entryService.registerListener(listener);
        }
        else
        {
            QMessageBox::warning(this, "Error", "Please choose Artist or Listener.");

            return;
        }

       QMessageBox::information(this,"Success", "Registration completed successfully.");

        LoginWindow *login = new LoginWindow(entryService, artistService);

        login->show();

        close();
    }

    catch(const SpotifyException& ex)
    {
        QMessageBox::warning(this,
                             "Spotify Error",
                             ex.what());
    }

    catch(const std::exception& ex)
    {
        QMessageBox::critical(this,
                              "Std Exception",
                              ex.what());
    }

    catch(...)
    {
        QMessageBox::critical(this,
                              "Unknown Error",
                              "Unknown exception.");
    }
}
RegisterWindow::~RegisterWindow()
{
    delete ui;
}
