#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include "entryservice.h"
#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(EntryService& entryService, QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_backButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::RegisterWindow *ui;

    EntryService& entryService;
};

#endif // REGISTERWINDOW_H
