#ifndef REF_H
#define REF_H

#include "Declarations.hpp"

template <typename T>
class Ref {
public:
    Ref(RepositoryElementId id, Repository<T> &repository) : id(id), repository(repository) {}

    RepositoryElementId get_id() const { return id; }

    Repository<T> &get_repository() const { return repository; }

private:
    const RepositoryElementId id;
    Repository<T> &repository;
};

#endif