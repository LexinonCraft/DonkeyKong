#include "TestStage.hpp"

#include "DK/model/entities/Barrel.hpp"
#include "DK/model/entities/Player.hpp"

TestStage::TestStage(int rng(), PlayerData &player_data) : Stage(rng, player_data) {
    lower_girder = entities.add_girder({100, -100}, {500, -300});
    upper_girder = entities.add_girder({100, -550}, {400, -350});
    player->enter_platform(lower_girder, 200);
}

void TestStage::spawn_lower_barrel() { barrel = entities.add_barrel({400, -400}); }

void TestStage::spawn_upper_barrel() {
    barrel = entities.add_barrel({200, -600});
    barrel->set_on_platform(upper_girder, get_barrel_roll_speed(), 1);
}

void TestStage::place_hammer() { auto hammer = entities.add_hammer_power_up(player->get_position() + sf::Vector2f{0, -20}); }

void TestStage::add_ladder() { ladder = entities.add_ladder(lower_girder, upper_girder, 300, false); }
