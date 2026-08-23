#ifndef SCORE_EFFECT_HPP
#define SCORE_EFFECT_HPP

#include <SFML/System/Vector2.hpp>

#include "DK/Constants.hpp"
#include "DK/view/Declarations.hpp"

/**
 * @brief Represents the state of the score effect that appears when the player scores points.
 */
class ScoreEffect {
public:
    /**
     * @brief Initialize the score effect.
     * @param origin The initial position of the score effect.
     * @param added_score The amount of score added.
     */
    ScoreEffect(sf::Vector2f origin, int added_score) : origin(origin), added_score(added_score) {}

    /**
     * @brief Updates the state of the score effect.
     *
     * @param dt Time elapsed since the last update.
     * @returns true If the score effect is still active.
     * @returns false If the score effect has expired.
     */
    bool update(float dt) {
        time_elapsed += dt;
        return time_elapsed < constants::SCORE_EFFECT_DURATION;
    }

    /**
     * @brief Draws the score effect on the specified layer stack.
     * @param layer_stack The layer stack where the score effect will be drawn.
     * @param assets_manager The assets manager used to retrieve the font.
     */
    void draw(LayerStack &layer_stack, AssetsManager &assets_manager);

private:
    float time_elapsed = 0.f;
    sf::Vector2f origin;
    int added_score;
};

#endif
