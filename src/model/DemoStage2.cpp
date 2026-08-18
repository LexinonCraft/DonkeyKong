#include <SFML/System/Vector2.hpp>

#include "DemoStage2.hpp"

/**
 * @brief Builds the prototype scene used for the current game demo.
 * @param id_generator Function used to create unique entity ids.
 */
DemoStage2::DemoStage2(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p4 = entities.add_girder({-100, -140}, {605, -200}, Girder::Color::Blue);
    auto p5 = entities.add_girder({-100, -340}, {605, -400}, Girder::Color::Blue);
    entities.add_ladder(p4, p5, 300.f, false, Ladder::Color::Yellow);
}

void DemoStage2::update_while_running(float dt) {
    time_since_last_spawn += dt;

    if (time_since_last_spawn > 2.0f) {
        entities.add_barrel({300, -500});
        time_since_last_spawn = 0.f;
    }    

    Stage::update_while_running(dt);
}
