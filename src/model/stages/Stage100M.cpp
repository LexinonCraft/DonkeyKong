#include <SFML/System/Vector2.hpp>

#include "Stage100M.hpp"

/**
 * @brief Builds the prototype scene used for the current game demo.
 * @param id_generator Function used to create unique entity ids.
 */
Stage100M::Stage100M(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p0 = entities.add_girder({0, -20}, {constants::VIEW_WIDTH, -20}, Girder::Color::Blue);
    auto p1 = entities.add_girder({20, -130}, {150, -130}, Girder::Color::Blue);
    auto p2 = entities.add_girder({170, -130}, {constants::VIEW_WIDTH - 170, -130}, Girder::Color::Blue);
    auto p3 = entities.add_girder({constants::VIEW_WIDTH - 150, -130}, {constants::VIEW_WIDTH - 20, -130}, Girder::Color::Blue);
}

void Stage100M::update_while_running(float dt) {
    time_since_last_spawn += dt;

    if (time_since_last_spawn > 2.0f) {
        // entities.add_barrel({300, -500});
        time_since_last_spawn = 0.f;
    }

    Stage::update_while_running(dt);
}
