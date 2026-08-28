#ifndef TITLE_SCREEN_CONTROL_HPP
#define TITLE_SCREEN_CONTROL_HPP

#include <optional>

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/TitleScreenView.hpp"

/**
 * @brief Control class for the title screen.
 */
class TitleScreenControl : public AbstractSceneControl {
public:
    /**
     * @brief Initialize with a view
     *
     * @param window The window to draw on
     * @param assets_manager The assets manager to load resources
     * @param player_data The global player data
     */
    TitleScreenControl(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data) : AbstractSceneControl(window) {
        title_screen_view.emplace(window, assets_manager, player_data);
    }

    /**
     * @brief Initialize without a view
     */
    TitleScreenControl() : AbstractSceneControl() {}

    void handle_event(sf::Event *event) override;

    void handle_input() override {}

    void update(float dt) override {
        if (title_screen_view.has_value()) {
            title_screen_view->update(dt);
        }
    }

    void draw() override {
        if (title_screen_view.has_value()) {
            title_screen_view->draw();
        }
    }

    NextScene get_next_scene() const override { return next_scene; }

private:
    std::optional<TitleScreenView> title_screen_view;
    NextScene next_scene = NextScene::Stay;
};

#endif
