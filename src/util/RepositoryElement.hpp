#ifndef REPOSITORY_ELEMENT_H
#define REPOSITORY_ELEMENT_H

#include "Ref.hpp"

template <typename T>
class RepositoryElement {
public:
    
    RepositoryElement(Ref<T> ref) : ref(ref) {}

    Ref<T> get_ref() const { return ref; }

    bool is_destroyed() const { return destroyed; }

protected:
    bool destroy() {
        if (destroyed) {
            return false;
        }

        destroyed = true;
        ref.get_repository().remove(ref);
        return true;
    }

private:
    const Ref<T> ref;
    bool destroyed = false;
};

#endif
