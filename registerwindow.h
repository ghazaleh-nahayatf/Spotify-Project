#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include "entryservice.h"
#include "artistservice.h"
#include "listenerservice.h"
#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(EntryService& entryService,
                            ArtistService& artistService,
                            ListenerService& listenerService,
                            QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_backButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::RegisterWindow *ui;

    EntryService& entryService;
    ArtistService& artistService;
    ListenerService& listenerService;
};

#endif // REGISTERWINDOW_H
