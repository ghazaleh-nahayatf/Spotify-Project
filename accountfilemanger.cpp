#include "accountfilemanger.h"
#include "account.h"
#include <fstream>
#include <sstream>

using namespace std;

void AccountFileManager::save(const vector<Account>& accounts)
{
    ofstream file("accounts.txt");

    if (!file.is_open())
        throw runtime_error("Cannot open accounts.txt");

    for (int i = 0; i < static_cast<int>(accounts.size()); i++)
    {
        file << accounts[i].getAccountId() << '|'
             << accounts[i].getFullName() << '|'
             << accounts[i].getUserName() << '|'
             << accounts[i].getPassword() << '|'
             << accounts[i].getBiography() << '|'
             << accounts[i].getRole()
             << '\n';
    }

    file.close();
}
vector<Account> AccountFileManager::load()
{
    vector<Account> accounts;

    ifstream file("accounts.txt");

    if (!file.is_open())
        return accounts;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string fullName;
        string userName;
        string password;
        string role;
        string biography;
        string ID;

        getline(ss, ID, '|');
        getline(ss, fullName, '|');
        getline(ss, userName, '|');
        getline(ss, password, '|');
        getline(ss, biography, '|');
        getline(ss, role, '|');

        Account account(
            fullName,
            userName,
            biography,
            stoi(ID),
            role,
            password);

        accounts.push_back(account);
    }

    file.close();

    return accounts;
}