#ifndef EDITPROFILEWINDOW_H
#define EDITPROFILEWINDOW_H

#include <QDialog>
#include "artistservice.h"
#include "listenerservice.h"

namespace Ui {
class EditProfileWindow;
}

class EditProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfileWindow(
        ArtistService &artistService,
        const Artist &artist,
        QWidget *parent = nullptr);
    EditProfileWindow(
        ListenerService& listenerService,
        const Listener &listener,
        QWidget *parent = nullptr);
    ~EditProfileWindow();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_passwordLineEdit_textChanged(const QString &arg1);

    void on_browsePhotoButton_clicked();

private:
    Ui::EditProfileWindow *ui;

    ArtistService* artistService = nullptr;
    ListenerService* listenerService = nullptr;

    Artist currentArtist;
    Listener currentListener;

    bool isArtist;
};

#endif // EDITPROFILEWINDOW_H
