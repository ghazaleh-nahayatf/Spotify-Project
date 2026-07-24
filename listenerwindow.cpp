#include "listenerwindow.h"
#include "ui_listenerwindow.h"

ListenerWindow::ListenerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListenerWindow)
{
    ui->setupUi(this);
}

ListenerWindow::~ListenerWindow()
{
    delete ui;
}

void ListenerWindow::on_createAlbumButton_clicked()
{

}

