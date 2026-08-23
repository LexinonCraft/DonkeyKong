#ifndef OBSERVER_REGISTRY_HPP
#define OBSERVER_REGISTRY_HPP

#include <unordered_map>

#include "DK/model/Declarations.hpp"

/**
 * @brief A registry for observers of type T.
 */
template <typename T> class ObserverRegistry {
public:
    /**
     * @brief Initialize the registry.
     *
     * @param id_generator A function that generates unique ids for observers.
     */
    ObserverRegistry(Id (*id_generator)()) : id_generator(id_generator) {}

    /**
     * @brief Registers an observer for events.
     * @param observer Observer to notify when events occur (reference must stay valid until unregistered).
     * @returns Observer id used to unregister this observer later.
     */
    Id register_observer(T &observer) {
        Id id = id_generator();
        observers[id] = &observer;
        return id;
    }

    /**
     * @brief Unregisters an observer from future events.
     * @param id Observer id returned by register_observer().
     */
    void unregister_observer(Id id) { observers.erase(id); }

    /** @returns An iterator to the beginning of the observer registry. */
    auto begin() { return observers.begin(); }

    /** @returns An iterator to the end of the observer registry. */
    auto end() { return observers.end(); }

private:
    std::unordered_map<Id, T *> observers;
    Id (*id_generator)();
};

#endif
