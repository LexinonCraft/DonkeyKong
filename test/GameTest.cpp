#include <cstdlib>
#include <gtest/gtest.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/control/GameOverControl.hpp"
#include "DK/control/StageControl.hpp"
#include "DK/control/StageTransitionControl.hpp"
#include "DK/control/TitleScreenControl.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/model/entities/Barrel.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

// clang-format off
#include "TestStage.hpp"
// clang-format on

#define SKIP_IF_NO_DISPLAY()                                                                                                               \
    if (std::getenv("DISPLAY") == nullptr) {                                                                                               \
        GTEST_SKIP() << "Skipping rendering-related test because there is no display.";                                                    \
    }

//  /$$    /$$ /$$                                 /$$                           /$$
// | $$   | $$|__/                                | $$                          | $$
// | $$   | $$ /$$  /$$$$$$  /$$  /$$  /$$       /$$$$$$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$$$$$$
// |  $$ / $$/| $$ /$$__  $$| $$ | $$ | $$      |_  $$_/   /$$__  $$ /$$_____/|_  $$_/  /$$_____/
//  \  $$ $$/ | $$| $$$$$$$$| $$ | $$ | $$        | $$    | $$$$$$$$|  $$$$$$   | $$   |  $$$$$$
//   \  $$$/  | $$| $$_____/| $$ | $$ | $$        | $$ /$$| $$_____/ \____  $$  | $$ /$$\____  $$
//    \  $/   | $$|  $$$$$$$|  $$$$$/$$$$/        |  $$$$/|  $$$$$$$ /$$$$$$$/  |  $$$$//$$$$$$$/
//     \_/    |__/ \_______/ \_____/\___/          \___/   \_______/|_______/    \___/ |_______/

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
    sf::RenderWindow window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "LayerStackTest.create_and_draw_layers");
    LayerStack layer_stack(window);
    layer_stack.clear_all();
    layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(sf::RectangleShape({100, 100}));
    layer_stack.draw_all();
}

//  /$$      /$$                 /$$           /$$         /$$                           /$$
// | $$$    /$$$                | $$          | $$        | $$                          | $$
// | $$$$  /$$$$  /$$$$$$   /$$$$$$$  /$$$$$$ | $$       /$$$$$$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$$$$$$
// | $$ $$/$$ $$ /$$__  $$ /$$__  $$ /$$__  $$| $$      |_  $$_/   /$$__  $$ /$$_____/|_  $$_/  /$$_____/
// | $$  $$$| $$| $$  \ $$| $$  | $$| $$$$$$$$| $$        | $$    | $$$$$$$$|  $$$$$$   | $$   |  $$$$$$
// | $$\  $ | $$| $$  | $$| $$  | $$| $$_____/| $$        | $$ /$$| $$_____/ \____  $$  | $$ /$$\____  $$
// | $$ \/  | $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$        |  $$$$/|  $$$$$$$ /$$$$$$$/  |  $$$$//$$$$$$$/
// |__/     |__/ \______/  \_______/ \_______/|__/         \___/   \_______/|_______/    \___/ |_______/

// =========================================================================================================================================
// Test the Player::update() method and its interaction with the Stage and Barrel indirectly through the TestStage class and its update()
// method.
class PlayerUpdateTest : public ::testing::Test {
protected:
    PlayerData player_data;
    TestStage stage{std::rand, player_data};
};

// Test that the player loses a life when hit by a barrel.
TEST_F(PlayerUpdateTest, player_hit_by_barrel) {
    stage.spawn_lower_barrel();
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
    stage.spawn_lower_barrel();
    for (int i = 0; i < 1000 && player_data.get_hammer_use_count() == 0; ++i) {
        stage.update(1.f / 60.f);
    }
    EXPECT_FALSE(stage.is_over());
    EXPECT_TRUE(stage.get_barrel()->is_destroyed());
    EXPECT_EQ(player_data.get_hammer_use_count(), 1u);
}

// Test that the player can jump over a barrel and survive.
TEST_F(PlayerUpdateTest, player_jumps_over_barrel) {
    stage.spawn_lower_barrel();
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
// =========================================================================================================================================

// =========================================================================================================================================
// Test the Barrel::update() method
class BarrelUpdateTest : public ::testing::Test {
protected:
    void SetUp() override { stage.get_player()->destroy(); }
    PlayerData player_data;
    TestStage stage{std::rand, player_data};
};

// Test that a barrel is destroyed after falling off the screen.
TEST_F(BarrelUpdateTest, barrel_destroyed_after_falling_off_screen) {
    stage.spawn_lower_barrel();
    EXPECT_FALSE(stage.get_barrel()->is_destroyed());

    for (int i = 0; i < 1000 && !stage.get_barrel()->is_destroyed(); ++i) {
        stage.update(1.f / 60.f);
    }

    EXPECT_TRUE(stage.get_barrel()->is_destroyed());
    EXPECT_LT(constants::BARREL_RADIUS, stage.get_barrel()->get_position().y);
}

// Test that a barrel rolls off the upper girder, falls, and lands on the lower girder, reversing direction.
TEST_F(BarrelUpdateTest, barrel_rolls_off_upper_girder_onto_lower_girder) {
    stage.spawn_upper_barrel();

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::OnGirder);
    EXPECT_EQ(stage.get_barrel()->get_current_platform(), stage.get_upper_girder());
    EXPECT_LT(0.f, stage.get_barrel()->get_vx());

    for (int i = 0; i < 1000 && stage.get_barrel()->get_state() == Barrel::State::OnGirder; ++i) {
        stage.update(1.f / 60.f);
    }

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::Falling);
    EXPECT_LT(0.f, stage.get_barrel()->get_vx());

    for (int i = 0; i < 1000 && stage.get_barrel()->get_state() == Barrel::State::Falling; ++i) {
        stage.update(1.f / 60.f);
    }

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::OnGirder);
    EXPECT_EQ(stage.get_barrel()->get_current_platform(), stage.get_lower_girder());
    EXPECT_LT(stage.get_barrel()->get_vx(), 0.f);
    EXPECT_LT(400, stage.get_barrel()->get_position().x);
}

// Test that a barrel rolls down a ladder when it reaches the ladder's position.
TEST_F(BarrelUpdateTest, barrel_rolls_down_ladder) {
    stage.add_ladder();
    stage.spawn_upper_barrel();

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::OnGirder);
    EXPECT_EQ(stage.get_barrel()->get_current_platform(), stage.get_upper_girder());
    EXPECT_LT(0.f, stage.get_barrel()->get_vx());

    for (int i = 0; i < 1000 && stage.get_barrel()->get_state() == Barrel::State::OnGirder; ++i) {
        stage.update(1.f / 60.f);
    }

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::RollingDownClimbable);
    EXPECT_EQ(stage.get_barrel()->get_current_climbable(), stage.get_ladder());
    EXPECT_EQ(300, stage.get_barrel()->get_position().x);
    EXPECT_EQ(0.f, stage.get_barrel()->get_vx());

    for (int i = 0; i < 1000 && stage.get_barrel()->get_state() == Barrel::State::RollingDownClimbable; ++i) {
        stage.update(1.f / 60.f);
    }

    EXPECT_EQ(stage.get_barrel()->get_state(), Barrel::State::OnGirder);
    EXPECT_EQ(stage.get_barrel()->get_current_platform(), stage.get_lower_girder());
    EXPECT_LT(stage.get_barrel()->get_vx(), 0.f);
    EXPECT_LE(stage.get_barrel()->get_position().x, 300);
}
// =========================================================================================================================================

// =========================================================================================================================================
// Test the EntityRepository::clear_secondary_entities() method
class EntityRepositoryTest : public ::testing::Test {
protected:
    PlayerData player_data;
    TestStage stage{std::rand, player_data};
};

// Test that clear_secondary_entities destroys active secondary entities, removes secondary entities from the
// pending additions queue, and leaves non-secondary entities untouched.
TEST_F(EntityRepositoryTest, clear_secondary_entities) {
    // Add a barrel and flush it into the active entities map.
    stage.spawn_lower_barrel();
    stage.get_entities().handle_additions();
    EXPECT_FALSE(stage.get_barrel()->is_destroyed());

    // Add a second barrel that stays in the pending additions queue (handle_additions not called yet).
    auto pending_barrel = stage.get_entities().add_barrel({300, -400});

    // Clear all secondary entities.
    stage.get_entities().clear_secondary_entities();

    // The already-active barrel must be marked as destroyed.
    EXPECT_TRUE(stage.get_barrel()->is_destroyed());

    // After processing additions the pending barrel must not appear in the repository.
    stage.get_entities().handle_additions();
    bool pending_barrel_added = false;
    for (const auto &[id, entity] : stage.get_entities()) {
        if (entity.get() == pending_barrel.get()) {
            pending_barrel_added = true;
        }
    }
    EXPECT_FALSE(pending_barrel_added);

    // Non-secondary entities (e.g. the player) must not be affected.
    EXPECT_FALSE(stage.get_player()->is_destroyed());
}
// =========================================================================================================================================

//   /$$$$$$                        /$$                         /$$         /$$                           /$$
//  /$$__  $$                      | $$                        | $$        | $$                          | $$
// | $$  \__/  /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$ | $$       /$$$$$$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$$$$$$
// | $$       /$$__  $$| $$__  $$|_  $$_/   /$$__  $$ /$$__  $$| $$      |_  $$_/   /$$__  $$ /$$_____/|_  $$_/  /$$_____/
// | $$      | $$  \ $$| $$  \ $$  | $$    | $$  \__/| $$  \ $$| $$        | $$    | $$$$$$$$|  $$$$$$   | $$   |  $$$$$$
// | $$    $$| $$  | $$| $$  | $$  | $$ /$$| $$      | $$  | $$| $$        | $$ /$$| $$_____/ \____  $$  | $$ /$$\____  $$
// |  $$$$$$/|  $$$$$$/| $$  | $$  |  $$$$/| $$      |  $$$$$$/| $$        |  $$$$/|  $$$$$$$ /$$$$$$$/  |  $$$$//$$$$$$$/
//  \______/  \______/ |__/  |__/   \___/  |__/       \______/ |__/         \___/   \_______/|_______/    \___/ |_______/

// =========================================================================================================================================
// Test the StageControl class
class StageControlTest : public ::testing::Test {
protected:
    void SetUp() override {
        stage_ptr = new TestStage(std::rand, player_data);
        stage_control.emplace(std::unique_ptr<TestStage>(stage_ptr));
    }

    PlayerData player_data;
    TestStage *stage_ptr{nullptr};
    std::optional<StageControl> stage_control;
};

// Test that the StageControl transitions to the GameOver scene when the player loses all lives.
TEST_F(StageControlTest, game_over) {
    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    for (unsigned int i = 0; i < constants::INITIAL_LIVES - 1; ++i) {
        player_data.lose_life();
    }

    stage_ptr->on_player_dying();

    for (int i = 0; i < 1000 && stage_control->get_next_scene() == AbstractSceneControl::NextScene::Stay; ++i) {
        stage_control->update(1.f / 60.f);
    }

    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::GameOver);
}

// Test that the StageControl transitions to the next stage when the player completes the current stage.
TEST_F(StageControlTest, advance_stage) {
    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    stage_ptr->start_exit_animation();

    for (int i = 0; i < 1000 && stage_control->get_next_scene() == AbstractSceneControl::NextScene::Stay; ++i) {
        stage_control->update(1.f / 60.f);
    }

    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::StageTransition);
    EXPECT_EQ(player_data.get_stage_in_level(), 1u);
}

// Test that the StageControl transitions to the same stage when the player dies and has lives remaining.
TEST_F(StageControlTest, repeat_stage) {
    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    stage_ptr->on_player_dying();

    for (int i = 0; i < 1000 && stage_control->get_next_scene() == AbstractSceneControl::NextScene::Stay; ++i) {
        stage_control->update(1.f / 60.f);
    }

    EXPECT_EQ(stage_control->get_next_scene(), AbstractSceneControl::NextScene::StageTransition);
    EXPECT_EQ(player_data.get_stage_in_level(), 0u);
}

// Test that pressing Space is forwarded to the player, causing the player to enter the InAir state.
TEST_F(StageControlTest, space_key_causes_player_to_jump) {
    EXPECT_EQ(stage_ptr->get_player()->get_state(), Player::State::OnPlatform);

    sf::Event::KeyPressed key_pressed_event;
    key_pressed_event.code = sf::Keyboard::Key::Space;
    sf::Event event(key_pressed_event);
    stage_control->handle_event(&event);

    // Update a few frames so the jump can take effect.
    for (int i = 0; i < 10; ++i) {
        stage_control->update(1.f / 60.f);
    }

    EXPECT_EQ(stage_ptr->get_player()->get_state(), Player::State::InAir);
}
// =========================================================================================================================================

// =========================================================================================================================================
// Test the StageTransitionControl class
class StageTransitionControlTest : public ::testing::Test {
protected:
    void SetUp() override { stage_transition_control.emplace(); }
    std::optional<StageTransitionControl> stage_transition_control;
};

// Test that the StageTransitionControl stays in the current scene before the transition duration has elapsed.
TEST_F(StageTransitionControlTest, stays_before_duration) {
    EXPECT_EQ(stage_transition_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    // Update for less than the required duration.
    const float dt = 1.f / 60.f;
    const int frames = static_cast<int>((constants::STAGE_TRANSITION_DURATION - 0.5f) / dt);
    for (int i = 0; i < frames; ++i) {
        stage_transition_control->update(dt);
    }

    EXPECT_EQ(stage_transition_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);
}

// Test that the StageTransitionControl transitions to the Stage scene after the transition duration has elapsed.
TEST_F(StageTransitionControlTest, transitions_to_stage_after_duration) {
    EXPECT_EQ(stage_transition_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    // Update for at least the required duration.
    const float dt = 1.f / 60.f;
    const int frames = static_cast<int>((constants::STAGE_TRANSITION_DURATION + 0.5f) / dt) + 1;
    for (int i = 0; i < frames; ++i) {
        stage_transition_control->update(dt);
    }

    EXPECT_EQ(stage_transition_control->get_next_scene(), AbstractSceneControl::NextScene::Stage);
}
// =========================================================================================================================================

// =========================================================================================================================================
// Test the GameOverControl class
class GameOverControlTest : public ::testing::Test {
protected:
    void SetUp() override { game_over_control.emplace(player_data); }
    PlayerData player_data;
    std::optional<GameOverControl> game_over_control;
};

// Test that the GameOverControl stays in the current scene before the game over duration has elapsed.
TEST_F(GameOverControlTest, stays_before_duration) {
    EXPECT_EQ(game_over_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    // Update for less than the required duration.
    const float dt = 1.f / 60.f;
    const int frames = static_cast<int>((constants::GAME_OVER_DURATION - 0.5f) / dt);
    for (int i = 0; i < frames; ++i) {
        game_over_control->update(dt);
    }

    EXPECT_EQ(game_over_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);
}

// Test that the GameOverControl transitions to the TitleScreen scene after the game over duration has elapsed.
TEST_F(GameOverControlTest, transitions_to_title_screen_after_duration) {
    EXPECT_EQ(game_over_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);

    // Update for at least the required duration.
    const float dt = 1.f / 60.f;
    const int frames = static_cast<int>((constants::GAME_OVER_DURATION + 0.5f) / dt) + 1;
    for (int i = 0; i < frames; ++i) {
        game_over_control->update(dt);
    }

    EXPECT_EQ(game_over_control->get_next_scene(), AbstractSceneControl::NextScene::TitleScreen);
}
// =========================================================================================================================================

// =========================================================================================================================================
// Test the TitleScreenControl class
class TitleScreenControlTest : public ::testing::Test {
protected:
    void SetUp() override { title_screen_control.emplace(); }
    PlayerData player_data;
    std::optional<TitleScreenControl> title_screen_control;
};

// Test that pressing the Enter key transitions from the title screen to the stage transition scene.
TEST_F(TitleScreenControlTest, press_enter) {
    EXPECT_EQ(title_screen_control->get_next_scene(), AbstractSceneControl::NextScene::Stay);
    sf::Event::KeyPressed key_pressed_event;
    key_pressed_event.code = sf::Keyboard::Key::Enter;
    sf::Event event(key_pressed_event);
    title_screen_control->handle_event(&event);
    EXPECT_EQ(title_screen_control->get_next_scene(), AbstractSceneControl::NextScene::StageTransition);
}
// =========================================================================================================================================

//  /$$   /$$   /$$     /$$ /$$         /$$                           /$$
// | $$  | $$  | $$    |__/| $$        | $$                          | $$
// | $$  | $$ /$$$$$$   /$$| $$       /$$$$$$    /$$$$$$   /$$$$$$$ /$$$$$$   /$$$$$$$
// | $$  | $$|_  $$_/  | $$| $$      |_  $$_/   /$$__  $$ /$$_____/|_  $$_/  /$$_____/
// | $$  | $$  | $$    | $$| $$        | $$    | $$$$$$$$|  $$$$$$   | $$   |  $$$$$$
// | $$  | $$  | $$ /$$| $$| $$        | $$ /$$| $$_____/ \____  $$  | $$ /$$\____  $$
// |  $$$$$$/  |  $$$$/| $$| $$        |  $$$$/|  $$$$$$$ /$$$$$$$/  |  $$$$//$$$$$$$/
//  \______/    \___/  |__/|__/         \___/   \_______/|_______/    \___/ |_______/

TEST(MathTest, floor_to_int) {
    EXPECT_EQ(floor_to_int(3.7f), 3);
    EXPECT_EQ(floor_to_int(-3.7f), -4);
    EXPECT_EQ(floor_to_int(0.f), 0);
}

TEST(MathTest, mod) {
    EXPECT_EQ(mod(5, 3), 2);
    EXPECT_EQ(mod(-5, 3), 1);
}

TEST(PositionsTest, get_absolute_position) {
    sf::Vector2f relative_position{10.f, 20.f};
    sf::Vector2f absolute_position = get_absolute_position(relative_position, AnchorPosition::TopLeft);
    EXPECT_LT((absolute_position - sf::Vector2f(10.f, -constants::VIEW_HEIGHT + 20.f)).length(), 0.001f);

    absolute_position = get_absolute_position(relative_position, AnchorPosition::Center);
    EXPECT_LT((absolute_position - sf::Vector2f(constants::VIEW_WIDTH / 2.f + 10.f, -constants::VIEW_HEIGHT / 2.f + 20.f)).length(),
              0.001f);
}
