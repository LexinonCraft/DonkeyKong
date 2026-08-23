#ifndef STAGE_OBSERVER_HPP
#define STAGE_OBSERVER_HPP

#include <SFML/System/Vector2.hpp>

/**
 * @brief Abstract class for observing stage events.
 */
class StageObserver {
public:
    virtual ~StageObserver() = default;

    /**
     * @brief Called when a score is added in the game.
     *
     * @param position The position where the event for adding the score occurred.
     * @param added_score The amount of score added.
     */
    virtual void on_score_added(sf::Vector2f position, int added_score) {}

    /**
     * @brief Called when the player dies in the game.
     */
    virtual void on_player_died() {}
};

#endif
