#ifndef SCORE_EFFECT_HPP
#define SCORE_EFFECT_HPP

#include <SFML/System/Vector2.hpp>

#include "DK/view/LayerStack.hpp"
#include "DK/view/AssetsManager.hpp"

class ScoreEffect {
public:
    ScoreEffect(sf::Vector2f origin, int added_score) : origin(origin), added_score(added_score) {}

    bool update(float dt);
    void draw(LayerStack &layer_stack, AssetsManager &assets_manager);

private:
    float time_elapsed = 0.f;
    sf::Vector2f origin;
    int added_score;
};

#endif
