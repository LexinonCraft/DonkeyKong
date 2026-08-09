#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <unordered_map>
#include <memory>

#include "Declarations.hpp"

template <typename T>
class Repository {
public:
    Repository(RepositoryElementId id_generator()) : id_generator(id_generator) {}

    virtual ~Repository() {}

    void delete_by_id(RepositoryElementId id) {
        elements.erase(id);
    }

    auto begin() const {
        return elements.begin();
    }

    auto end() const {
        return elements.end();
    }

protected:
    template <typename U>
    std::shared_ptr<U> add(Ref<T> ref, std::shared_ptr<U> element) {
        elements[ref.get_id()] = std::dynamic_pointer_cast<T>(element);
        return element;
    }

    Ref<T> gen_ref() {
        return Ref<T>(id_generator(), *this);
    }
    
private:
    std::unordered_map<RepositoryElementId, std::shared_ptr<T>> elements;
    RepositoryElementId (*id_generator)();
};

#endif
