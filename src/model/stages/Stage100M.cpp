#include <memory>

#include <SFML/System/Vector2.hpp>

#include "Stage100M.hpp"
#include "../../util/Math.hpp"

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

    spawn_suitable_girders.push_back(p0);
    spawn_suitable_girders.push_back(p1);
    spawn_suitable_girders.push_back(p2);
    spawn_suitable_girders.push_back(p3);
    spawn_suitable_girders.push_back(p4);
    spawn_suitable_girders.push_back(p5);
    spawn_suitable_girders.push_back(p6);
    spawn_suitable_girders.push_back(p7);
    spawn_suitable_girders.push_back(p8);
    spawn_suitable_girders.push_back(p9);
    spawn_suitable_girders.push_back(p10);
    spawn_suitable_girders.push_back(p11);
    spawn_suitable_girders.push_back(p12);
    // not p13, because it is not reachable by the player and thus not suitable for spawning.

    lower_falling_girders.push_back(p2);
    lower_falling_girders.push_back(p5);
    lower_falling_girders.push_back(p8);
    lower_falling_girders.push_back(p11);
    upper_falling_girder = p13;

    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -130}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -130}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -230}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -230}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -330}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -330}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({160, -430}, 30));
    dissolving_platforms.push_back(entities.add_dissolving_platform({constants::VIEW_WIDTH - 160, -430}, 30));

    entities.add_ladder(p0, p1, 30.f, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p0, p2, 300.f, false, Ladder::Color::Yellow));
    entities.add_ladder(p0, p3, constants::VIEW_WIDTH - 30.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p1, p4, 50.f, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p2, p5, 200.f, false, Ladder::Color::Yellow));
    static_entities_to_be_cleared.push_back(entities.add_ladder(p2, p5, constants::VIEW_WIDTH - 200.f, false, Ladder::Color::Yellow));
    entities.add_ladder(p3, p6, constants::VIEW_WIDTH - 50.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p4, p7, 70.f, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p5, p8, 300.f, false, Ladder::Color::Yellow));
    entities.add_ladder(p6, p9, constants::VIEW_WIDTH - 70.f, false, Ladder::Color::Yellow);
    entities.add_ladder(p7, p10, 90.f, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p8, p11, 190.f, false, Ladder::Color::Yellow));
    static_entities_to_be_cleared.push_back(entities.add_ladder(p8, p11, constants::VIEW_WIDTH - 190.f, false, Ladder::Color::Yellow));
    entities.add_ladder(p9, p12, constants::VIEW_WIDTH - 90.f, false, Ladder::Color::Yellow);

    static_entities_to_be_cleared.push_back(entities.add_beam(p11, p13, 220.f));
    static_entities_to_be_cleared.push_back(entities.add_beam(p11, p13, constants::VIEW_WIDTH - 220.f));

    entities.add_hammer_power_up(p4->get_left() - sf::Vector2f(0.f, constants::HAMMER_Y_OFFSET));
    entities.add_hammer_power_up(sf::Vector2f(300.f, -330 - constants::HAMMER_Y_OFFSET));

    donkey_kong = entities.add_donkey_kong(p11, constants::VIEW_WIDTH / 2.f, false);
    pauline = entities.add_pauline(p13, 200.f);

    player->enter_platform(p0, 50);

    for (unsigned int i = 0; i < constants::STAGE_100M_INITIAL_GHOST_COUNT; ++i) {
        spawn_ghost();
    }
}

void Stage100M::update_while_running(float dt) {
    time_since_last_spawn += dt;

    if (time_since_last_spawn > constants::GHOST_SPAWN_INTERVAL) {
        if (ghost_count < constants::STAGE_100M_MAX_GHOST_COUNT) {
            spawn_ghost();
        }
        time_since_last_spawn = 0.f;
    }

    bool all_dissolved = true;
    for (auto it = dissolving_platforms.begin(); all_dissolved && it != dissolving_platforms.end(); ++it) {
        auto platform = *it;
        if (!platform->has_dissolved()) {
            all_dissolved = false;
        }
    }
    if (all_dissolved) {
        on_completed();
    }

    Stage::update_while_running(dt);
}

void Stage100M::spawn_ghost() {
    while (true) {
        std::shared_ptr<Girder> random_girder = spawn_suitable_girders[mod(random_int(), spawn_suitable_girders.size())];
        float x = random_girder->get_left().x + mod(random_int(), constants::GHOST_SPAWN_X_POS_STEPS) * (random_girder->get_right().x - random_girder->get_left().x) / constants::GHOST_SPAWN_X_POS_STEPS;

        auto diff = sf::Vector2f{x, random_girder->surface_y_at(x)} - player->get_position();
        float distance = diff.length();
        if (distance < constants::GHOST_SPAWN_MIN_DISTANCE) {
            continue;
        }

        entities.add_ghost(random_girder, x);
        ghost_count++;
        break;
    }
}
