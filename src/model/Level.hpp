#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>

#include "Declarations.hpp"

/// An abstract level
class Level {
public:
    virtual ~Level() {}

    const std::unordered_map<int, Platform &> &get_platforms() const;
    const std::unordered_map<int, Ladder &> &get_ladders() const;
    const std::unordered_map<int, Entity &> &get_entities() const;

    Platform *get_platform(int id) const;
    Ladder *get_ladder(int id) const;
    Entity *get_entity(int id) const;

    virtual void set_player(int id_generator(), Player *player);

    virtual void update(float dt);

protected:
    Level();

    int add_platform(int id_generator(), Platform *platform);
    int add_ladder(int id_generator(), Ladder *ladder);
    int add_entity(int id_generator(), Entity *entity);

    Platform *remove_platform(int id);
    Ladder *remove_ladder(int id);
    Entity *remove_entity(int id);

private:
    std::unordered_map<int, Platform &> platforms;
    std::unordered_map<int, Ladder &> ladders;
    std::unordered_map<int, Entity &> entities;
};

#endif
