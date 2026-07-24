#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include "spotifyexception.h"
#include "artistwindow.h"
#include "listenerwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(EntryService& entryService, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LoginWindow),
    entryService(entryService)
{
    ui->setupUi(this);
}
void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    if(username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please fill all fields.");

        return;
    }

    try
    {
        Account account =
            entryService.login(
                username.toStdString(),
                password.toStdString());

        QMessageBox::information( this,"Success", "Login successful.");

        if(account.getRole() == "Artist")
        {
            QMessageBox::information(this, "Artist", "Welcome Artist");
            ArtistWindow *artistWindow = new ArtistWindow();
            artistWindow->show();

            this->close();
        }
        else if(account.getRole() == "Listener")
        {
            QMessageBox::information(this, "Listener",  "Welcome Listener");
            ListenerWindow *window = new ListenerWindow();
            window->show();

            this->close();
        }

        close();
    }

    catch(const SpotifyException& ex)
    {
        QMessageBox::warning( this, "Error", ex.what());

        ui->passwordLineEdit->clear();
        ui->passwordLineEdit->setFocus();
    }
}
void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow *window = new RegisterWindow(entryService);

    window->show();

    close();
}


LoginWindow::~LoginWindow()
{
    delete ui;
}
