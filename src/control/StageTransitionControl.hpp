#ifndef STAGE_TRANSITION_CONTROL_HPP
#define STAGE_TRANSITION_CONTROL_HPP

#include <optional>

#include "DK/Constants.hpp"
#include "DK/control/AbstractSceneControl.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/StageTransitionView.hpp"

/**
 * @brief Control class for the stage transition scene.
 *
 */
class StageTransitionControl : public AbstractSceneControl {
public:
    /**
     * @brief Initialize with a view
     *
     * @param window The window to draw on
     * @param player_data The global player data
     * @param assets_manager The assets manager to load resources
     */
    StageTransitionControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : AbstractSceneControl(window) {
        stage_transition_view.emplace(window, assets_manager, player_data);
    }

    /**
     * @brief Initialize without a view
     */
    StageTransitionControl() : AbstractSceneControl() {}

    void handle_event(sf::Event *event) override {}

    void handle_input() override {}

    void update(float dt) override { time_elapsed += dt; }

    void draw() override {
        if (stage_transition_view.has_value()) {
            stage_transition_view->draw();
        }
    }

    NextScene get_next_scene() const override {
        return time_elapsed >= constants::STAGE_TRANSITION_DURATION ? NextScene::Stage : NextScene::Stay;
    }

private:
    std::optional<StageTransitionView> stage_transition_view;
    float time_elapsed = 0.f;
};

#endif
