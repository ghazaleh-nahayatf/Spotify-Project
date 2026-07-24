#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QWidget>
#include "entryservice.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(EntryService& entryService, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    EntryService& entryService;
};

#endif // LOGINWINDOW_H
