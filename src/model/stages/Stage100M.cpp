#include <SFML/System/Vector2.hpp>

#include "Stage100M.hpp"

/**
 * @brief Builds the prototype scene used for the current game demo.
 * @param id_generator Function used to create unique entity ids.
 */
Stage100M::Stage100M(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p0 = entities.add_girder({0, -20}, {constants::VIEW_WIDTH, -20}, Girder::Color::Blue);
    auto p1 = entities.add_girder({20, -130}, {145, -130}, Girder::Color::Blue);
    auto p2 = entities.add_girder({175, -130}, {constants::VIEW_WIDTH - 175, -130}, Girder::Color::Blue);
    auto p3 = entities.add_girder({constants::VIEW_WIDTH - 145, -130}, {constants::VIEW_WIDTH - 20, -130}, Girder::Color::Blue);
    auto p4 = entities.add_girder({40, -230}, {145, -230}, Girder::Color::Blue);
    auto p5 = entities.add_girder({175, -230}, {constants::VIEW_WIDTH - 175, -230}, Girder::Color::Blue);
    auto p6 = entities.add_girder({constants::VIEW_WIDTH - 145, -230}, {constants::VIEW_WIDTH - 40, -230}, Girder::Color::Blue);
    auto p7 = entities.add_girder({60, -330}, {145, -330}, Girder::Color::Blue);
    auto p8 = entities.add_girder({175, -330}, {constants::VIEW_WIDTH - 175, -330}, Girder::Color::Blue);
    auto p9 = entities.add_girder({constants::VIEW_WIDTH - 145, -330}, {constants::VIEW_WIDTH - 60, -330}, Girder::Color::Blue);
    auto p10 = entities.add_girder({80, -430}, {145, -430}, Girder::Color::Blue);
    auto p11 = entities.add_girder({175, -430}, {constants::VIEW_WIDTH - 175, -430}, Girder::Color::Blue);
    auto p12 = entities.add_girder({constants::VIEW_WIDTH - 145, -430}, {constants::VIEW_WIDTH - 80, -430}, Girder::Color::Blue);
    auto p13 = entities.add_girder({145, -550}, {constants::VIEW_WIDTH - 145, -550}, Girder::Color::Blue);

    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -130}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -130}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -230}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -230}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -330}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -330}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -430}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -430}, 30));

    entities.add_ladder(p0, p1, 30.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p0, p2, 300.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p0, p3, constants::VIEW_WIDTH - 30.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p1, p4, 50.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p2, p5, 200.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p2, p5, constants::VIEW_WIDTH - 200.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p3, p6, constants::VIEW_WIDTH - 50.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p4, p7, 70.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p5, p8, 300.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p6, p9, constants::VIEW_WIDTH - 70.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p7, p10, 90.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p8, p11, 190.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p8, p11, constants::VIEW_WIDTH - 190.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p9, p12, constants::VIEW_WIDTH - 90.f, false, Ladder::Color::Yellow);

    player->enter_platform(p0, 50);
}

void Stage100M::update_while_running(float dt) {
    bool all_dissolved = true;
    for (auto it = dissolving_platforms.begin(); all_dissolved && it != dissolving_platforms.end(); ++it) {
        if (!(*it)->has_dissolved()) {
            all_dissolved = false;
        }
    }
    if (all_dissolved) {
        on_completed();
    }

    Stage::update_while_running(dt);
}
