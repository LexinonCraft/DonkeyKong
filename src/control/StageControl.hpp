#ifndef STAGE_CONTROL_HPP
#define STAGE_CONTROL_HPP

#include <cstdlib>
#include <memory>
#include <optional>

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/model/Declarations.hpp"
#include "DK/model/StageSequence.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/StageView.hpp"

/**
 * @brief Control class for the main game screen. It owns the Stage and StageView, and handles user input, updates the game state, and
 * renders the scene.
 *
 */
class StageControl : public AbstractSceneControl {
public:
    StageControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager, std::unique_ptr<Stage> stage)
        : AbstractSceneControl(window), stage(std::move(stage)) {
        stage_view.emplace(window, *this->stage, assets_manager);
    }

    StageControl(PlayerData &player_data, std::unique_ptr<Stage> stage) : AbstractSceneControl(), stage(std::move(stage)) {}

    StageControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : StageControl(window, player_data, assets_manager, create_stage(std::rand, player_data)) {}

    StageControl(PlayerData &player_data) : StageControl(player_data, create_stage(std::rand, player_data)) {}

    virtual ~StageControl() {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

    /** @returns The managed Stage instance. */
    Stage &get_stage() { return *stage; }

private:
    std::unique_ptr<Stage> stage;
    std::optional<StageView> stage_view;
    bool left_pressed = false;
    bool right_pressed = false;
    bool up_pressed = false;
    bool down_pressed = false;
};

#endif
