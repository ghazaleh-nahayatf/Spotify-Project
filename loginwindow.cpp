#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registerwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}
void LoginWindow::on_registerButton_clicked()
{
    RegisterWindow *registerWindow = new RegisterWindow();

    registerWindow->show();

    this->close();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
