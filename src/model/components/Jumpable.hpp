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
    void update(float dt) {
        cooldown_time_remaining -= dt;
        if (cooldown_time_remaining < 0.f) {
            cooldown_time_remaining = 0.f;
        }
    }

    void on_jump_over() {
        cooldown_time_remaining = constants::JUMPABLE_COOLDOWN_TIME;
    }

    bool is_on_cooldown() const {
        return cooldown_time_remaining > 0.f;
    }

private:
    float cooldown_time_remaining = 0.f;
};

#endif
