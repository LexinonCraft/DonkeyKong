#ifndef PAULINE_HPP
#define PAULINE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/animations/AbstractAnimation.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/util/BaseEntity.hpp"
#include "DK/model/util/EntityVisitor.hpp"

class Pauline : public BaseEntity {
public:
    enum class State {
        Normal,
        Animated,
    };

    Pauline(Ref ref, std::shared_ptr<Platform> platform, float x_position)
        : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

    void accept(EntityVisitor &visitor) override { visitor.visit(*this); }

    sf::Vector2f get_position() const { return position; }

    void set_position(sf::Vector2f new_position) { position = new_position; }

    State get_state() const { return state; }
    void set_state(State new_state) { state = new_state; }

    void start_animation(AbstractAnimation *animation) {
        current_animation = animation;
        set_state(State::Animated);
    }

    void stop_animation() {
        current_animation = nullptr;
        set_state(State::Normal);
    }

    AbstractAnimation *get_current_animation() const { return current_animation; }

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f position;
    State state = State::Normal;
    AbstractAnimation *current_animation = nullptr;
};

#endif
