#include "accountrepository.h"
#include "accountfilemanger.h"
#include "account.h"

AccountRepository::AccountRepository()
{
    accounts = AccountFileManager::load();
    nextAccountId = 1;

    for (int i = 0; i < static_cast<int>(accounts.size()); i++)
    {
        if(accounts[i].getAccountId() >= nextAccountId)
            nextAccountId = accounts[i].getAccountId() + 1;
    }
}
optional<int> AccountRepository::save(const Account& entity)
{
    for (int i = 0; i < static_cast<int>(accounts.size()); i++)
    {
        if (accounts[i].getAccountId() == entity.getAccountId())
        {
            accounts[i] = entity;
            AccountFileManager::save(accounts);
            return accounts[i].getAccountId();
        }
    }

    Account newAccount = entity;
    newAccount.setAccountId(nextAccountId++);

    accounts.push_back(newAccount);

    AccountFileManager::save(accounts);

    return newAccount.getAccountId();
}
bool AccountRepository::remove(int id)
{
    for (int i = 0; i < static_cast<int>(accounts.size()); i++)
    {
        if (accounts[i].getAccountId() == id)
        {
            accounts.erase(accounts.begin() + i );
            AccountFileManager::save(accounts);
            return true;
        }
    }
    return false;
}
optional<Account> AccountRepository::search(int id)
{
    for (int i = 0; i < static_cast<int>(accounts.size()); i++)
    {
        if(accounts[i].getAccountId() == id)
        {
            return accounts[i];
        }
    }
    return nullopt;
}
