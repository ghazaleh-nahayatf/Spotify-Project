#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H

#include <QWidget>

namespace Ui {
class ListenerWindow;
}

class ListenerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ListenerWindow(QWidget *parent = nullptr);
    ~ListenerWindow();

private slots:
    void on_createAlbumButton_clicked();

private:
    Ui::ListenerWindow *ui;
};

#endif // LISTENERWINDOW_H
