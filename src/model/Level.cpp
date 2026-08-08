#include "Level.hpp"
#include "Player.hpp"
#include <memory>

PlatformRepository &Level::get_platforms() {
    return platforms;
}

LadderRepository &Level::get_ladders() {
    return ladders;
}

EntityRepository &Level::get_entities() {
    return entities;
}

std::shared_ptr<Player> Level::get_player() const {
    return player;
}

void Level::set_player(std::shared_ptr<Player> player) {
    this->player = player;
}

void Level::update(float dt) {
    for (auto it = platforms.begin(); it != platforms.end(); ++it) {
        it->second->update(dt);
    }
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        it->second->update(*this, dt);
    }
}

Level::Level(RepositoryElementId id_generator())
    : platforms(id_generator),
      ladders(id_generator),
      entities(id_generator) {
    auto player_ref = entities.add_player();
    set_player(std::dynamic_pointer_cast<Player>(player_ref.get()));
}
