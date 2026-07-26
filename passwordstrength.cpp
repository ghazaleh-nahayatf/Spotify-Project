#include "passwordstrength.h"
#include <QRegularExpression>

PasswordStrength::PasswordStrength() {}

QString PasswordStrength::passStrength(const QString &password)
{
    QRegularExpression strong( "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z\\d]).{12,}$");

    if(strong.match(password).hasMatch())
        return "Strong";

    QRegularExpression medium( "^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z\\d]).{6,}$");

    if(medium.match(password).hasMatch())
        return "Medium";

    return "Weak";
}