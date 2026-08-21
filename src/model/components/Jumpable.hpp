#ifndef JUMPABLE_HPP
#define JUMPABLE_HPP

#include <SFML/System/Vector2.hpp>

#include "../util/EntityFromComponentAux.hpp"
#include "../../Constants.hpp"

class Jumpable : public EntityFromComponentAux {
public:
    virtual ~Jumpable() {}

    virtual void check_jumps_over(sf::Vector2f player_position, Stage &stage) = 0;

protected:
    void update(float dt, Stage &stage) {
        cooldown_time_remaining -= dt;
        if (on_cooldown && cooldown_time_remaining < 0.f) {
            cooldown_time_remaining = 0.f;
            on_cooldown = false;
            on_cooldown_end(stage);
        }
    }

    void on_jump_over() {
        cooldown_time_remaining = constants::JUMPABLE_COOLDOWN_TIME;
        on_cooldown = true;
    }

    bool is_on_cooldown() const {
        return on_cooldown;
    }

    virtual void on_cooldown_end(Stage &stage) = 0;

private:
    float cooldown_time_remaining = 0.f;
    bool on_cooldown = false;
};

#endif
