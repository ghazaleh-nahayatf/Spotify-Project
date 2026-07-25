#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QWidget>
#include "account.h"
#include "artistservice.h"

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QWidget
{
    Q_OBJECT

public:
   explicit ArtistWindow(const Account &account,
                          ArtistService &artistService,
                          QWidget *parent = nullptr);
    ~ArtistWindow();

private slots:
    void on_createAlbumButton_clicked();

private:
    Ui::ArtistWindow *ui;

    Account currentAccount;
    ArtistService &artistService;
    void loadAlbums();
};

#endif // ARTISTWINDOW_H
