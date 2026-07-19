#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H
#include <optional>
template<typename T>

class AbstractRepository
{
public:
    AbstractRepository() = default;

    virtual std::optional<int> save(const T& entity) = 0;
    virtual bool remove(int id) = 0;
    virtual std::optional<T> search(int id) = 0;

    virtual ~AbstractRepository(){}
};

#endif // ABSTRACTREPOSITORY_H
