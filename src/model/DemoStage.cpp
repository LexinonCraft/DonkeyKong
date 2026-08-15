#include <SFML/System/Vector2.hpp>

#include "DemoStage.hpp"

/**
 * @brief Builds the prototype scene used for the current game demo.
 * @param id_generator Function used to create unique entity ids.
 */
DemoStage::DemoStage(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p1 = entities.add_girder({120, -500}, {500, -460});
    auto p2 = entities.add_girder({80, -360}, {540, -400});
    auto p3 = entities.add_girder({40, -300}, {520, -260});
    auto p4 = entities.add_girder({80, -160}, {560, -200});

    entities.add_ladder(p2, p1, 200.0f);
    entities.add_ladder(p3, p2, 300.0f);
    entities.add_ladder(p4, p3, 500.0f);
}

void DemoStage::update(float dt) {
    time_since_last_spawn += dt;

    if (time_since_last_spawn > 2.0f) {
        entities.add_barrel({300, -500});
        time_since_last_spawn = 0.f;
    }

    Stage::update(dt);
}
