#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include "abstractrepository.h"
#include "account.h"
#include <vector>
#include <optional>

class AccountRepository : public AbstractRepository<Account>
{
private:
    vector<Account> accounts;
    int nextAccountId = 1 ;
public:
    AccountRepository();

    optional<int> save(const Account& entity) override;

    bool remove(int id) override;

    optional<Account> search(int id) override;

    virtual optional<Account> searchByUserName(const string& userName) = 0;
};

#endif // ACCOUNTREPOSITORY_H
