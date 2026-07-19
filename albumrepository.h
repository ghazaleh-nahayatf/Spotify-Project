#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H
#include <vector>
#include <optional>

#include "abstractrepository.h"
#include "album.h"

using namespace std;

class AlbumRepository : public AbstractRepository<Album>
{
private:
    vector<Album> albums;
    int nextAlbumId = 1 ;
public:
    AlbumRepository();

    optional<int> save(const Album& entity) override;

    bool remove(int id) override;

    optional<Album> search(int id) override;

    vector<Album> getByArtist(int artistId);
};

#endif // ALBUMREPOSITORY_H
