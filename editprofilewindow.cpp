#include "editprofilewindow.h"
#include "ui_editprofilewindow.h"

EditProfileWindow::EditProfileWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfileWindow)
{
    ui->setupUi(this);
}

EditProfileWindow::~EditProfileWindow()
{
    delete ui;
}
