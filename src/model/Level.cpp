#include "Level.hpp"

Level::Level(Id id_generator()) : entities(id_generator), updatable_components(entities), platform_components(entities) {
    // auto player_ref = entities.add_player();
    // set_player(std::dynamic_pointer_cast<Player>(player_ref.get()));
}

void Level::update(float dt) {
    updatable_components.update_all(dt, *this);
}
