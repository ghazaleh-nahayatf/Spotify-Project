#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"
#include "spotifyexception.h"
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
        }
        else if(account.getRole() == "Listener")
        {
            QMessageBox::information(this, "Listener",  "Welcome Listener");
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
