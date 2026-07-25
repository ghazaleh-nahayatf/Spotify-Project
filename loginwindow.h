#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWidget>
#include "entryservice.h"
#include "artistservice.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(EntryService& entryService,
                ArtistService& artistService,
                QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    EntryService& entryService;
    ArtistService& artistService;
};

#endif // LOGINWINDOW_H
