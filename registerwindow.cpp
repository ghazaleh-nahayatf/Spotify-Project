#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "loginwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}
void RegisterWindow::on_backButton_clicked()
{
    LoginWindow *loginWindow = new LoginWindow();

    loginWindow->show();

    this->close();
}
RegisterWindow::~RegisterWindow()
{
    delete ui;
}
