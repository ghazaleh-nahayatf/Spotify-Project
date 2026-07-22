#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H

#include "accountrepository.h"
#include "artist.h"
#include <vector>
#include <optional>

class ArtistRepository : public AccountRepository
{
private:
    std::vector<Artist> artists;
    int nextArtistId = 1;

public:
    ArtistRepository();

    std::optional<int> save(const Artist& entity);

    bool remove(int id);

    std::optional<Artist> search(int id);

    vector<Artist> getAll();

    std::optional<Account> searchByUserName(const std::string& username) override;
};

#endif // ARTISTREPOSITORY_H
