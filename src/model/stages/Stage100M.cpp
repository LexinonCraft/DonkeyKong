#include "DK/model/stages/Stage100M.hpp"

#include <memory>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/entities/Beam.hpp"
#include "DK/model/entities/DissolvingPlatform.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/util/Math.hpp"

namespace {
constexpr float BOTTOM_GIRDER_Y = -20.f;
constexpr float FIRST_ROW_Y = -130.f;
constexpr float SECOND_ROW_Y = -230.f;
constexpr float THIRD_ROW_Y = -330.f;
constexpr float FOURTH_ROW_Y = -430.f;
constexpr float TOP_GIRDER_Y = -550.f;
constexpr float SIDE_GIRDER_INNER_X = 145.f;
constexpr float CENTER_GIRDER_OUTER_X = 175.f;
constexpr float FIRST_ROW_MARGIN = 20.f;
constexpr float SECOND_ROW_MARGIN = 40.f;
constexpr float THIRD_ROW_MARGIN = 60.f;
constexpr float FOURTH_ROW_MARGIN = 80.f;

constexpr float DISSOLVING_PLATFORM_X = 160.f;
constexpr float DISSOLVING_PLATFORM_WIDTH = 30.f;

constexpr float BOTTOM_LEFT_LADDER_X = 30.f;
constexpr float BOTTOM_CENTER_LADDER_X = 300.f;
constexpr float FIRST_ROW_LEFT_LADDER_X = 50.f;
constexpr float FIRST_ROW_CENTER_LADDER_X = 200.f;
constexpr float SECOND_ROW_LEFT_LADDER_X = 70.f;
constexpr float SECOND_ROW_CENTER_LADDER_X = 300.f;
constexpr float THIRD_ROW_LEFT_LADDER_X = 90.f;
constexpr float THIRD_ROW_CENTER_LADDER_X = 190.f;
constexpr float TOP_BEAM_X = 220.f;

constexpr float HAMMER_X = 300.f;
constexpr float PAULINE_X = 200.f;
constexpr float PLAYER_START_X = 50.f;
} // namespace

Stage100M::Stage100M(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    // create girders
    auto p0 = entities.add_girder({0.f, BOTTOM_GIRDER_Y}, {constants::VIEW_WIDTH, BOTTOM_GIRDER_Y}, Girder::Color::Blue);
    auto p1 = entities.add_girder({FIRST_ROW_MARGIN, FIRST_ROW_Y}, {SIDE_GIRDER_INNER_X, FIRST_ROW_Y}, Girder::Color::Blue);
    auto p2 = entities.add_girder({CENTER_GIRDER_OUTER_X, FIRST_ROW_Y}, {constants::VIEW_WIDTH - CENTER_GIRDER_OUTER_X, FIRST_ROW_Y},
                                  Girder::Color::Blue);
    auto p3 = entities.add_girder({constants::VIEW_WIDTH - SIDE_GIRDER_INNER_X, FIRST_ROW_Y},
                                  {constants::VIEW_WIDTH - FIRST_ROW_MARGIN, FIRST_ROW_Y}, Girder::Color::Blue);
    auto p4 = entities.add_girder({SECOND_ROW_MARGIN, SECOND_ROW_Y}, {SIDE_GIRDER_INNER_X, SECOND_ROW_Y}, Girder::Color::Blue);
    auto p5 = entities.add_girder({CENTER_GIRDER_OUTER_X, SECOND_ROW_Y}, {constants::VIEW_WIDTH - CENTER_GIRDER_OUTER_X, SECOND_ROW_Y},
                                  Girder::Color::Blue);
    auto p6 = entities.add_girder({constants::VIEW_WIDTH - SIDE_GIRDER_INNER_X, SECOND_ROW_Y},
                                  {constants::VIEW_WIDTH - SECOND_ROW_MARGIN, SECOND_ROW_Y}, Girder::Color::Blue);
    auto p7 = entities.add_girder({THIRD_ROW_MARGIN, THIRD_ROW_Y}, {SIDE_GIRDER_INNER_X, THIRD_ROW_Y}, Girder::Color::Blue);
    auto p8 = entities.add_girder({CENTER_GIRDER_OUTER_X, THIRD_ROW_Y}, {constants::VIEW_WIDTH - CENTER_GIRDER_OUTER_X, THIRD_ROW_Y},
                                  Girder::Color::Blue);
    auto p9 = entities.add_girder({constants::VIEW_WIDTH - SIDE_GIRDER_INNER_X, THIRD_ROW_Y},
                                  {constants::VIEW_WIDTH - THIRD_ROW_MARGIN, THIRD_ROW_Y}, Girder::Color::Blue);
    auto p10 = entities.add_girder({FOURTH_ROW_MARGIN, FOURTH_ROW_Y}, {SIDE_GIRDER_INNER_X, FOURTH_ROW_Y}, Girder::Color::Blue);
    auto p11 = entities.add_girder({CENTER_GIRDER_OUTER_X, FOURTH_ROW_Y}, {constants::VIEW_WIDTH - CENTER_GIRDER_OUTER_X, FOURTH_ROW_Y},
                                   Girder::Color::Blue);
    auto p12 = entities.add_girder({constants::VIEW_WIDTH - SIDE_GIRDER_INNER_X, FOURTH_ROW_Y},
                                   {constants::VIEW_WIDTH - FOURTH_ROW_MARGIN, FOURTH_ROW_Y}, Girder::Color::Blue);
    auto p13 = entities.add_girder({SIDE_GIRDER_INNER_X, TOP_GIRDER_Y}, {constants::VIEW_WIDTH - SIDE_GIRDER_INNER_X, TOP_GIRDER_Y},
                                   Girder::Color::Blue);

    // add girders to the list of suitable girders for spawning ghosts
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

    // create list of lower falling girders and the upper falling girder for the completion animation
    lower_falling_girders.push_back(p2);
    lower_falling_girders.push_back(p5);
    lower_falling_girders.push_back(p8);
    lower_falling_girders.push_back(p11);
    upper_falling_girder = p13;

    // create dissolving platforms
    dissolving_platforms.push_back(entities.add_dissolving_platform({DISSOLVING_PLATFORM_X, FIRST_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(
        entities.add_dissolving_platform({constants::VIEW_WIDTH - DISSOLVING_PLATFORM_X, FIRST_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(entities.add_dissolving_platform({DISSOLVING_PLATFORM_X, SECOND_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(
        entities.add_dissolving_platform({constants::VIEW_WIDTH - DISSOLVING_PLATFORM_X, SECOND_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(entities.add_dissolving_platform({DISSOLVING_PLATFORM_X, THIRD_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(
        entities.add_dissolving_platform({constants::VIEW_WIDTH - DISSOLVING_PLATFORM_X, THIRD_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(entities.add_dissolving_platform({DISSOLVING_PLATFORM_X, FOURTH_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));
    dissolving_platforms.push_back(
        entities.add_dissolving_platform({constants::VIEW_WIDTH - DISSOLVING_PLATFORM_X, FOURTH_ROW_Y}, DISSOLVING_PLATFORM_WIDTH));

    // create ladders
    entities.add_ladder(p0, p1, BOTTOM_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p0, p2, BOTTOM_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    entities.add_ladder(p0, p3, constants::VIEW_WIDTH - BOTTOM_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    entities.add_ladder(p1, p4, FIRST_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p2, p5, FIRST_ROW_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    static_entities_to_be_cleared.push_back(
        entities.add_ladder(p2, p5, constants::VIEW_WIDTH - FIRST_ROW_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    entities.add_ladder(p3, p6, constants::VIEW_WIDTH - FIRST_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    entities.add_ladder(p4, p7, SECOND_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p5, p8, SECOND_ROW_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    entities.add_ladder(p6, p9, constants::VIEW_WIDTH - SECOND_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    entities.add_ladder(p7, p10, THIRD_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);
    static_entities_to_be_cleared.push_back(entities.add_ladder(p8, p11, THIRD_ROW_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    static_entities_to_be_cleared.push_back(
        entities.add_ladder(p8, p11, constants::VIEW_WIDTH - THIRD_ROW_CENTER_LADDER_X, false, Ladder::Color::Yellow));
    entities.add_ladder(p9, p12, constants::VIEW_WIDTH - THIRD_ROW_LEFT_LADDER_X, false, Ladder::Color::Yellow);

    // create beams
    static_entities_to_be_cleared.push_back(entities.add_beam(p11, p13, TOP_BEAM_X));
    static_entities_to_be_cleared.push_back(entities.add_beam(p11, p13, constants::VIEW_WIDTH - TOP_BEAM_X));

    // add hammer power-ups
    entities.add_hammer_power_up(p4->get_left() - sf::Vector2f(0.f, constants::HAMMER_Y_OFFSET));
    entities.add_hammer_power_up(sf::Vector2f(HAMMER_X, THIRD_ROW_Y - constants::HAMMER_Y_OFFSET));

    // add Donkey Kong and Pauline
    donkey_kong = entities.add_donkey_kong(p11, constants::VIEW_WIDTH / 2.f, false);
    pauline = entities.add_pauline(p13, PAULINE_X);

    // set player position
    player->enter_platform(p0, PLAYER_START_X);

    observer_id = get_entities().get_observer_registry().register_observer(*this);

    // spawn initial ghosts
    for (unsigned int i = 0; i < constants::STAGE_100M_INITIAL_GHOST_COUNT; ++i) {
        spawn_ghost();
    }
}

Stage100M::~Stage100M() { get_entities().get_observer_registry().unregister_observer(observer_id); }

void Stage100M::on_completed() {
    clear_secondary_entities();
    for (auto it = static_entities_to_be_cleared.begin(); it != static_entities_to_be_cleared.end(); ++it) {
        it->get()->destroy();
    }

    current_animation =
        std::make_unique<Stage100MCompletionAnimation>(*this, lower_falling_girders, upper_falling_girder, player, donkey_kong, pauline);
}

void Stage100M::update_while_running(float dt) {
    time_since_last_spawn += dt;

    // spawn more ghosts over time
    if (time_since_last_spawn > constants::GHOST_SPAWN_INTERVAL) {
        if (ghost_count < constants::STAGE_100M_MAX_GHOST_COUNT) {
            spawn_ghost();
        }
        time_since_last_spawn = 0.f;
    }

    // check if all dissolving platforms have dissolved, and if yes run on_completed()
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
        float x = random_girder->get_left().x + mod(random_int(), constants::GHOST_SPAWN_X_POS_STEPS) *
                                                    (random_girder->get_right().x - random_girder->get_left().x) /
                                                    constants::GHOST_SPAWN_X_POS_STEPS;

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

void Stage100M::on_entity_removed(std::shared_ptr<BaseEntity> entity) {
    IsGhostChecker checker;
    entity->accept(checker);
    if (checker.is_ghost) {
        ghost_count--;
    }
}
