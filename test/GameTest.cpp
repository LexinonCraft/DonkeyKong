#include "TestStage.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/model/entities/Barrel.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

#define SKIP_IF_NO_DISPLAY()                                                                                                               \
    if (std::getenv("DISPLAY") == nullptr) {                                                                                               \
        GTEST_SKIP() << "Skipping rendering-related test because there is no display.";                                                    \
    }

// #include "../src/model/Barrel.hpp"
// #include "../src/model/Girder.hpp"
// #include "../src/../Constants.hpp"

// These tests exercise the barrel/girder physics directly. They construct only
// model objects (which hold CPU-side SFML shapes, no window), so they run headless.

/*
namespace {
constexpr float R = constants::BARREL_RADIUS;

// two overlapping girders: g0 slopes down-right, g1 (below it) down-left, so a
// barrel rolling off g0's right end drops onto g1 and reverses direction.
std::vector<Girder> two_girder_stage() {
    std::vector<Girder> girders;
    girders.emplace_back(sf::Vector2f{0, -200}, sf::Vector2f{100, -160}); // down-right
    girders.emplace_back(sf::Vector2f{0, -60},  sf::Vector2f{140, -100}); // down-left
    return girders;
}

Barrel barrel_on(const Girder& g) {
    Barrel barrel({g.high_end().x, g.high_end().y - R});
    barrel.set_on_girder(g);
    return barrel;
}
} // namespace

TEST(GirderTest, geometry) {
    Girder down_right({0, -200}, {100, -160}); // slope 0.4, lower end on the right
    EXPECT_FLOAT_EQ(down_right.slope(), 0.4f);
    EXPECT_FLOAT_EQ(down_right.surface_y_at(50), -180.f);
    EXPECT_EQ(down_right.downhill_sign(), 1);
    EXPECT_FLOAT_EQ(down_right.high_end().x, 0.f);

    Girder down_left({0, -60}, {100, -100}); // lower end on the left
    EXPECT_EQ(down_left.downhill_sign(), -1);
    EXPECT_FLOAT_EQ(down_left.high_end().x, 100.f);
}

TEST(BarrelTest, rolls_glued_to_the_slope) {
    std::vector<Girder> girders = two_girder_stage();
    Barrel barrel = barrel_on(girders[0]);

    barrel.update(0.1f, girders);

    EXPECT_EQ(barrel.get_state(), Barrel::State::OnGirder);
    EXPECT_FLOAT_EQ(barrel.get_position().x, constants::ROLL_SPEED * 0.1f); // moved downhill
    EXPECT_FLOAT_EQ(barrel.get_position().y,                               // y follows the surface
                    girders[0].surface_y_at(barrel.get_position().x) - R);
}

TEST(BarrelTest, zig_zags_onto_the_next_girder) {
    std::vector<Girder> girders = two_girder_stage();
    Barrel barrel = barrel_on(girders[0]);
    ASSERT_GT(barrel.get_vx(), 0.f); // rolling right on g0

    // run until it rolls off g0, falls, and settles on g1 (now rolling left)
    for (int i = 0; i < 2000 &&
         !(barrel.get_state() == Barrel::State::OnGirder && barrel.get_vx() < 0.f); ++i) {
        barrel.update(1.f / 60.f, girders);
    }

    EXPECT_EQ(barrel.get_state(), Barrel::State::OnGirder);
    EXPECT_LT(barrel.get_vx(), 0.f); // direction flipped on the down-left girder
    EXPECT_NEAR(barrel.get_position().y,
                girders[1].surface_y_at(barrel.get_position().x) - R, 0.001f);
}
*/

// Test that AssetsManager can load assets and that a texture can be drawn to a render texture without crashing.
TEST(AssetsManagerTest, load_assets_and_draw_texture) {
    SKIP_IF_NO_DISPLAY();
    AssetsManager assets_manager; // assets are loaded here
    sf::RenderTexture render_texture({300, 300});
    sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::DonkeyKongAngry1));
    render_texture.draw(sprite);
    render_texture.display();
}

// Test that LayerStack can be created, cleared, and drawn without crashing.
TEST(LayerStackTest, create_and_draw_layers) {
    SKIP_IF_NO_DISPLAY();
    sf::RenderWindow window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong");
    LayerStack layer_stack(window);
    layer_stack.clear_all();
    layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(sf::RectangleShape({100, 100}));
    layer_stack.draw_all();
}

// Test the Player::update() method and its interaction with the Stage and Barrel indirectly through the TestStage class and its update()
// method.
class PlayerUpdateTest : public ::testing::Test {
protected:
    PlayerData player_data;
    TestStage stage{std::rand, player_data};
};

// Test that the player loses a life when hit by a barrel.
TEST_F(PlayerUpdateTest, player_hit_by_barrel) {
    unsigned int previous_lives = player_data.get_lives();
    for (int i = 0; i < 1000 && !stage.is_over(); ++i) {
        stage.update(1.f / 60.f);
    }
    EXPECT_TRUE(stage.is_over());
    EXPECT_EQ(player_data.get_lives(), previous_lives - 1);
}

// Test that the player can destroy a barrel by hitting it with a hammer.
TEST_F(PlayerUpdateTest, player_hammers_barrel) {
    stage.place_hammer();
    for (int i = 0; i < 1000 && player_data.get_hammer_use_count() == 0; ++i) {
        stage.update(1.f / 60.f);
    }
    EXPECT_FALSE(stage.is_over());
    EXPECT_TRUE(stage.get_barrel()->is_destroyed());
    EXPECT_EQ(player_data.get_hammer_use_count(), 1);
}

// Test that the player can jump over a barrel and survive.
TEST_F(PlayerUpdateTest, player_jumps_over_barrel) {
    bool has_jumped = false;
    for (int i = 0; i < 1000 && !stage.is_over() && (!has_jumped || stage.get_player()->get_state() == Player::State::InAir); ++i) {
        if (stage.get_barrel()->get_position().x - stage.get_player()->get_position().x < 50.f && !has_jumped) {
            stage.get_player()->jump();
            has_jumped = true;
        }
        stage.update(1.f / 60.f);
    }
    EXPECT_TRUE(stage.get_player()->get_state() == Player::State::OnPlatform);
    EXPECT_FALSE(stage.is_over());
    EXPECT_FALSE(stage.get_barrel()->is_destroyed());
    EXPECT_LT(0u, player_data.get_score());
}
