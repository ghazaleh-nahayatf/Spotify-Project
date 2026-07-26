#ifndef PASSWORDSTRENGTH_H
#define PASSWORDSTRENGTH_H

#include <QString>

class PasswordStrength
{
public:
    PasswordStrength();
    static QString passStrength(const QString& password);
};

#endif // PASSWORDSTRENGTH_H
