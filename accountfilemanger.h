#ifndef ACCOUNTFILEMANGER_H
#define ACCOUNTFILEMANGER_H
#include "account.h"
#include<vector>

class AccountFileManager
{
public:
    static void save(const vector<Account>& accounts);
    static vector<Account> load();
};

#endif // ACCOUNTFILEMANGER_H
