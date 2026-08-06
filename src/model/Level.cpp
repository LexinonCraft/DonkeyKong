#include "Level.hpp"
#include "Platform.hpp"
#include "Ladder.hpp"
#include "Entity.hpp"
#include "Player.hpp"

const std::unordered_map<int, Platform &> &Level::get_platforms() const {
    return platforms;
}

const std::unordered_map<int, Ladder &> &Level::get_ladders() const {
    return ladders;
}

const std::unordered_map<int, Entity &> &Level::get_entities() const {
    return entities;
}

Platform *Level::get_platform(int id) const {
    auto it = platforms.find(id);
    if (it == platforms.end()) {
        return nullptr;
    }
    return &it->second;
}

Ladder *Level::get_ladder(int id) const {
    auto it = ladders.find(id);
    if (it == ladders.end()) {
        return nullptr;
    }
    return &it->second;
}

Entity *Level::get_entity(int id) const {
    auto it = entities.find(id);
    if (it == entities.end()) {
        return nullptr;
    }
    return &it->second;
}

void Level::set_player(int id_generator(), Player *player) {
    add_entity(id_generator, player);
}

void Level::update(float dt) {
    for (auto it = platforms.begin(); it != platforms.end(); ++it) {
        Platform &platform = it->second;
        platform.update(dt);
    }
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        Entity &entity = it->second;
        entity.update(*this, dt);
    }
}

Level::Level() {}

int Level::add_platform(int id_generator(), Platform *platform) {
    int id = id_generator();
    platforms.emplace(id, *platform);
    return id;
}

int Level::add_ladder(int id_generator(), Ladder *ladder) {
    int id = id_generator();
    ladders.emplace(id, *ladder);
    return id;
}

int Level::add_entity(int id_generator(), Entity *entity) {
    int id = id_generator();
    entities.emplace(id, *entity);
    return id;
}

Platform *Level::remove_platform(int id) {
    auto it = platforms.find(id);
    if (it == platforms.end()) {
        return nullptr;
    }
    platforms.erase(it);
    return &it->second;
}

Ladder *Level::remove_ladder(int id) {
    auto it = ladders.find(id);
    if (it == ladders.end()) {
        return nullptr;
    }
    ladders.erase(it);
    return &it->second;
}

Entity *Level::remove_entity(int id) {
    auto it = entities.find(id);
    if (it == entities.end()) {
        return nullptr;
    }
    entities.erase(it);
    return &it->second;
}
