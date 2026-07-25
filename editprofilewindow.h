#ifndef EDITPROFILEWINDOW_H
#define EDITPROFILEWINDOW_H

#include <QDialog>

namespace Ui {
class EditProfileWindow;
}

class EditProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfileWindow(QWidget *parent = nullptr);
    ~EditProfileWindow();

private:
    Ui::EditProfileWindow *ui;
};

#endif // EDITPROFILEWINDOW_H
