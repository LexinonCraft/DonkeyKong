#ifndef STAGE_VIEW_HPP
#define STAGE_VIEW_HPP

#include <list>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"
#include "../model/Stage.hpp"
#include "DrawableComponentRepository.hpp"
#include "ScoreEffect.hpp"

/**
 * @brief View component that renders a whole stage using layered SFML textures.
 */
class StageView : public AbstractSceneView, private StageObserver {
public:
    /**
     * @brief Creates the stage view and binds it to a specific stage.
     * @param window Window used for rendering.
     * @param stage Stage whose entities are rendered.
     */
    StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &assets_manager);

    ~StageView() override;

    /**
     * @brief Renders the current state of the stage.
     */
    void draw();

    void update(float dt, Stage &stage);

private:
    DrawableComponentRepository drawable_components;
    Stage &stage;
    std::list<ScoreEffect> current_score_effects;
    Id stage_observer_id;

    void on_score_added(sf::Vector2f position, int score_to_add) override;

    void on_player_died() override;
};

#endif
