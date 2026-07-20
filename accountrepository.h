#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include "account.h"
#include <optional>
class AccountRepository
{
public:
    virtual std::optional<Account> searchByUserName(
        const string& username)=0;

    virtual ~AccountRepository()=default;
};

#endif // ACCOUNTREPOSITORY_H
