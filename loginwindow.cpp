#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"

LoginWindow::LoginWindow(EntryService& entryService, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LoginWindow),
    entryService(entryService)
{
    ui->setupUi(this);
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
