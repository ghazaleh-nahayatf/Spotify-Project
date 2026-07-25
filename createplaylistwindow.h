#ifndef CREATEPLAYLISTWINDOW_H
#define CREATEPLAYLISTWINDOW_H

#include <QDialog>
#include "listenerservice.h"

namespace Ui {
class CreatePlaylistWindow;
}

class CreatePlaylistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePlaylistWindow(
        ListenerService& listenerService,
        int listenerId,
        QWidget *parent = nullptr);
    ~CreatePlaylistWindow();

private slots:
    void on_createButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreatePlaylistWindow *ui;
    ListenerService& listenerService;

    int listenerId;
};

#endif // CREATEPLAYLISTWINDOW_H
