#ifndef STAGE_VIEW_HPP
#define STAGE_VIEW_HPP

#include <list>

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/model/Stage.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponentRepository.hpp"
#include "DK/view/ScoreEffect.hpp"
#include "DK/view/views/AbstractSceneView.hpp"

/**
 * @brief View for rendering the entire stage.
 */
class StageView : public AbstractSceneView, private StageObserver {
public:
    /**
     * @brief Creates the stage view and binds it to a specific stage.
     * @param window Window used for rendering.
     * @param stage Stage whose entities are rendered.
     * @param assets_manager Assets manager to retrieve assets from.
     */
    StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &assets_manager);

    ~StageView() override;

    /**
     * @brief Renders the current state of the stage.
     */
    void draw();

    /**
     * @brief Update the view state based on the current state of the stage.
     * 
     * @param dt Time delta since the last update.
     */
    void update(float dt);

private:
    DrawableComponentRepository drawable_components;
    Stage &stage;
    std::list<ScoreEffect> current_score_effects;
    Id stage_observer_id;

    /**
     * @brief Create the score effect when the player scores points.
     * 
     * @param position The position where the score effect should be displayed.
     * @param score_to_add The amount of score added.
     */
    void on_score_added(sf::Vector2f position, int score_to_add) override { current_score_effects.emplace_back(position, score_to_add); }

    /**
     * @brief Clears the current score effects when the player dies.
     */
    void on_player_died() override { current_score_effects.clear(); }
};

#endif
