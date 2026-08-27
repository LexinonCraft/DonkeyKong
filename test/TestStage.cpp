#include "TestStage.hpp"

#include "DK/model/entities/Player.hpp"

TestStage::TestStage(int rng(), PlayerData &player_data) : Stage(rng, player_data) {
    girder = entities.add_girder({100, -100}, {500, -300});
    player->enter_platform(girder, 200);
}

void TestStage::spawn_barrel() { barrel = entities.add_barrel({400, -400}); }

void TestStage::place_hammer() { auto hammer = entities.add_hammer_power_up(player->get_position() + sf::Vector2f{0, -20}); }
