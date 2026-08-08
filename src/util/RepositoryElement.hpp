#ifndef REPOSITORY_ELEMENT_H
#define REPOSITORY_ELEMENT_H

#include "Ref.hpp"

template <typename T>
class RepositoryElement {
public:
    RepositoryElement(Ref<T> ref) : ref(ref) {}

    Ref<T> get_ref() const { return ref; }

private:
    const Ref<T> ref;
};

#endif