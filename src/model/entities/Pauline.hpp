#ifndef PAULINE_HPP
#define PAULINE_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Stage character whose position and state can be controlled by completion animations.
 */
class Pauline : public BaseEntity {
public:
    enum class State {
        Normal,
        Animated,
    };

    Pauline(Ref ref, std::shared_ptr<Platform> platform, float x_position);

    void accept(EntityVisitor &visitor) override;

    sf::Vector2f get_position() const { return position; }

    void set_position(sf::Vector2f new_position) { position = new_position; }

    State get_state() const { return state; }
    void set_state(State new_state) { state = new_state; }

    /**
     * @brief Lets an animation control Pauline's state and position.
     * @param animation Animation that takes control of the entity.
     */
    void start_animation(AbstractAnimation *animation);

    /** @brief Returns Pauline to her normal state. */
    void stop_animation();

    AbstractAnimation *get_current_animation() const { return current_animation; }

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f position;
    State state = State::Normal;
    AbstractAnimation *current_animation = nullptr;
};

#endif
