#ifndef PAULINE_RENDERER_HPP
#define PAULINE_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"
#include "DK/view/LayerStack.hpp"

/**
 * @brief Renderer for the Pauline entity.
 */
class PaulineRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the Pauline renderer for a concrete entity.
     * @param pauline Pauline instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    PaulineRenderer(std::shared_ptr<Pauline> pauline, AssetsManager &assets_manager) : pauline(pauline), assets_manager(assets_manager) {}

    /**
     * @brief Draws Pauline into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

    /**
     * @brief Update the timer for the scream animation and check whether to suppress the scream based on the stage's running state.
     *
     * @param dt Time delta since the last update.
     * @param stage The current stage, used to determine if the scream should be suppressed.
     */
    void update(float dt, Stage &stage) override;

private:
    std::shared_ptr<Pauline> pauline;
    AssetsManager &assets_manager;
    float animation_timer = 0.0f;
    bool suppress_scream = false;

    /**
     * @brief Internal animation visitor class for handling Pauline's animations.
     */
    class PaulineAnimationVisitor : public AnimationVisitor {
    public:
        bool draw_pauline = true;
        bool draw_heart = false;
        bool heart_broken = false;

        void visit(Stage25MCompletionAnimation &animation) override;

        void visit(Stage100MCompletionAnimation &animation) override;
    };
};

#endif
