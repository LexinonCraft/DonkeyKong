#ifndef STAGE_OBSERVER_HPP
#define STAGE_OBSERVER_HPP

#include <SFML/System/Vector2.hpp>

class StageObserver {
public:
    virtual ~StageObserver() = default;

    virtual void on_score_added(sf::Vector2f position, int added_score) = 0;
};

#endif
