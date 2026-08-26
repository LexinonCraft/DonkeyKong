#include "DK/model/stages/Stage25M.hpp"

#include <SFML/System/Vector2.hpp>

#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/Player.hpp"

namespace {
constexpr sf::Vector2f GIRDER_0_LEFT{-100.f, -20.f};
constexpr sf::Vector2f GIRDER_0_RIGHT{constants::VIEW_WIDTH / 2.f, -20.f};
constexpr sf::Vector2f GIRDER_1_LEFT{constants::VIEW_WIDTH / 2.f, -20.f};
constexpr sf::Vector2f GIRDER_1_RIGHT{constants::VIEW_WIDTH + 100.f, -40.f};
constexpr sf::Vector2f GIRDER_2_LEFT{0.f, -140.f};
constexpr sf::Vector2f GIRDER_2_RIGHT{constants::VIEW_WIDTH - 50.f, -100.f};
constexpr sf::Vector2f GIRDER_3_LEFT{50.f, -200.f};
constexpr sf::Vector2f GIRDER_3_RIGHT{constants::VIEW_WIDTH, -240.f};
constexpr sf::Vector2f GIRDER_4_LEFT{0.f, -350.f};
constexpr sf::Vector2f GIRDER_4_RIGHT{constants::VIEW_WIDTH - 50.f, -310.f};
constexpr sf::Vector2f GIRDER_5_LEFT{50.f, -410.f};
constexpr sf::Vector2f GIRDER_5_RIGHT{constants::VIEW_WIDTH, -450.f};
constexpr sf::Vector2f GIRDER_6_LEFT{380.f, -520.f};
constexpr sf::Vector2f GIRDER_6_RIGHT{constants::VIEW_WIDTH - 50.f, -510.f};
constexpr sf::Vector2f GIRDER_7_LEFT{0.f, -520.f};
constexpr sf::Vector2f GIRDER_7_RIGHT{380.f, -520.f};
constexpr sf::Vector2f GIRDER_8_LEFT{230.f, -610.f};
constexpr sf::Vector2f GIRDER_8_RIGHT{360.f, -610.f};

constexpr float LADDER_0_X = 220.f;
constexpr float LADDER_1_X = 500.f;
constexpr float LADDER_2_X = 260.f;
constexpr float LADDER_3_X = 90.f;
constexpr float LADDER_4_X = 180.f;
constexpr float LADDER_5_X = 300.f;
constexpr float LADDER_6_X = 500.f;
constexpr float LADDER_7_X = 450.f;
constexpr float LADDER_8_X = 200.f;
constexpr float LADDER_9_X = 100.f;
constexpr float LADDER_10_X = 240.f;
constexpr float LADDER_11_X = 490.f;
constexpr float LADDER_12_X = 340.f;

constexpr float HAMMER_0_X = 500.f;
constexpr float HAMMER_1_X = 100.f;
constexpr float DONKEY_KONG_X = 100.f;
constexpr float BARREL_STACK_X = 30.f;
constexpr float PAULINE_X = 275.f;
constexpr float EXIT_LADDER_0_PLATFORM_X = 195.f;
constexpr float EXIT_LADDER_0_X = 190.f;
constexpr float EXIT_LADDER_1_PLATFORM_X = 220.f;
constexpr float EXIT_LADDER_1_X = 220.f;
constexpr float EXIT_LADDER_UPPER_Y = -750.f;
constexpr float PLAYER_START_X = 50.f;
} // namespace

Stage25M::Stage25M(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    // create girders
    auto p0 = entities.add_girder(GIRDER_0_LEFT, GIRDER_0_RIGHT);
    auto p1 = entities.add_girder(GIRDER_1_LEFT, GIRDER_1_RIGHT);
    auto p2 = entities.add_girder(GIRDER_2_LEFT, GIRDER_2_RIGHT);
    auto p3 = entities.add_girder(GIRDER_3_LEFT, GIRDER_3_RIGHT);
    auto p4 = entities.add_girder(GIRDER_4_LEFT, GIRDER_4_RIGHT);
    auto p5 = entities.add_girder(GIRDER_5_LEFT, GIRDER_5_RIGHT);
    auto p6 = entities.add_girder(GIRDER_6_LEFT, GIRDER_6_RIGHT);
    auto p7 = entities.add_girder(GIRDER_7_LEFT, GIRDER_7_RIGHT);
    auto p8 = entities.add_girder(GIRDER_8_LEFT, GIRDER_8_RIGHT);

    // set barrel exit y position
    barrel_exit_y = p0->surface_y_at(0.f);

    // create ladders
    entities.add_ladder(p0, p2, LADDER_0_X, true);
    entities.add_ladder(p1, p2, LADDER_1_X, false);
    entities.add_ladder(p2, p3, LADDER_2_X, false);
    entities.add_ladder(p2, p3, LADDER_3_X, false);
    entities.add_ladder(p3, p4, LADDER_4_X, true);
    entities.add_ladder(p3, p4, LADDER_5_X, false);
    entities.add_ladder(p3, p4, LADDER_6_X, false);
    entities.add_ladder(p4, p5, LADDER_7_X, true);
    entities.add_ladder(p4, p5, LADDER_8_X, false);
    entities.add_ladder(p4, p5, LADDER_9_X, false);
    entities.add_ladder(p5, p7, LADDER_10_X, false);
    entities.add_ladder(p5, p6, LADDER_11_X, false);
    entities.add_ladder(p7, p8, LADDER_12_X, false);

    // create hammer power ups
    entities.add_hammer_power_up({HAMMER_0_X, p2->surface_y_at(HAMMER_0_X) - constants::HAMMER_Y_OFFSET});
    entities.add_hammer_power_up({HAMMER_1_X, p5->surface_y_at(HAMMER_1_X) - constants::HAMMER_Y_OFFSET});

    // set final girder for triggering the completion animation
    final_girder = p8;

    // create Donkey Kong, Pauline and barrel stack
    donkey_kong = entities.add_donkey_kong(p7, DONKEY_KONG_X, true);
    entities.add_barrel_stack(p7, BARREL_STACK_X);
    pauline = entities.add_pauline(p8, PAULINE_X);

    // create ladders leading to the next stage
    entities.add_ladder(p7->surface_y_at(EXIT_LADDER_0_PLATFORM_X), EXIT_LADDER_UPPER_Y, EXIT_LADDER_0_X, false, Ladder::Color::Cyan,
                        false);
    entities.add_ladder(p7->surface_y_at(EXIT_LADDER_1_PLATFORM_X), EXIT_LADDER_UPPER_Y, EXIT_LADDER_1_X, false, Ladder::Color::Cyan,
                        false);

    // set player starting position
    player->enter_platform(p0, PLAYER_START_X);
}

bool Stage25M::is_barrel_boundary_gap(const sf::Vector2f &position) const {
    const auto left_boundary = get_left_boundary();
    return left_boundary && position.x < *left_boundary && position.y >= barrel_exit_y;
}

void Stage25M::on_completed() { current_animation = std::make_unique<Stage25MCompletionAnimation>(*this, player, donkey_kong, pauline); }

void Stage25M::update_while_running(float dt) {
    if (player->get_current_platform() == final_girder) {
        on_completed();
    }

    Stage::update_while_running(dt);
}
