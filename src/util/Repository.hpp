#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <unordered_map>
#include <memory>

#include "Declarations.hpp"
#include "Ref.hpp"

template <typename T>
class Repository {
public:
    Repository(RepositoryElementId id_generator()) : id_generator(id_generator) {}

    virtual ~Repository() {}

    std::shared_ptr<T> get_by_ref(Ref<T> id) const;

    bool contains_ref(Ref<T> id) const;

    bool delete_by_ref(Ref<T> id);

    auto begin() const {
        return elements.begin();
    }

    auto end() const {
        return elements.end();
    }

protected:
    void add(Ref<T> ref, std::shared_ptr<T> element);

    Ref<T> gen_ref() {
        return Ref<T>(id_generator(), *this);
    }
    
private:
    std::unordered_map<RepositoryElementId, std::shared_ptr<T>> elements;
    RepositoryElementId (*id_generator)();
};

template <typename T>
void Repository<T>::add(Ref<T> ref, std::shared_ptr<T> element) {
    elements[ref.get_id()] = element;
}

template <typename T>
std::shared_ptr<T> Repository<T>::get_by_ref(Ref<T> id) const {
    auto it = elements.find(id.get_id());
    if (it == elements.end()) {
        return nullptr;
    }
    return it->second;
}

template <typename T>
bool Repository<T>::contains_ref(Ref<T> id) const {
    return elements.find(id.get_id()) != elements.end();
}

template <typename T>
bool Repository<T>::delete_by_ref(Ref<T> id) {
    auto it = elements.find(id.get_id());
    if (it != elements.end()) {
        elements.erase(it);
        return true;
    }
    return false;
}

#endif
