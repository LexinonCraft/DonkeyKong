#include "Level.hpp"

Level::Level(Id id_generator()) : entities(id_generator), updatable_components(entities), platform_components(entities), climbable_components(entities), player(entities.add_player()) {}

void Level::update(float dt) {
    updatable_components.update_all(dt, *this);
}
