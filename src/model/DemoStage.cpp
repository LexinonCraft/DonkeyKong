#include <SFML/System/Vector2.hpp>

#include "DemoStage.hpp"

/**
 * @brief Builds the prototype scene used for the current game demo.
 * @param id_generator Function used to create unique entity ids.
 */
DemoStage::DemoStage(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p0 = entities.add_girder({200, -600}, {400, -600});
    auto p1 = entities.add_girder({-5, -500}, {500, -460});
    auto p2 = entities.add_girder({70, -360}, {605, -400});
    auto p3 = entities.add_girder({-5, -300}, {550, -260});
    auto p4 = entities.add_girder({-100, -140}, {605, -200});

    entities.add_ladder(p1, p0, 300.0f, false);
    entities.add_ladder(p2, p1, 200.0f, false);
    entities.add_ladder(p3, p2, 300.0f, false);
    entities.add_ladder(p4, p3, 500.0f, false);

    final_girder = p0;
}

void DemoStage::update_while_running(float dt) {
    time_since_last_spawn += dt;

    if (time_since_last_spawn > 2.0f) {
        entities.add_barrel({300, -500});
        time_since_last_spawn = 0.f;
    }

    if (player->get_current_platform() == final_girder) {
        on_completed();
    }

    Stage::update_while_running(dt);
}
