#ifndef REF_H
#define REF_H

#include <memory>

#include "Declarations.hpp"

template <typename T>
class Ref {
public:
    Ref(RepositoryElementId id, Repository<T> &repository) : id(id), repository(repository) {}

    Ref(const Ref<T> &other) : id(other.id), repository(other.repository) {}

    Ref<T>& operator=(const Ref<T> &other) {
        if (this != &other) {
            id = other.id;
            repository = other.repository;
        }
        return *this;
    }

    RepositoryElementId get_id() const { return id; }

    std::shared_ptr<T> get() const {
        return repository.get_by_ref(*this);
    }

private:
    RepositoryElementId id;
    Repository<T> &repository;
};

#endif
