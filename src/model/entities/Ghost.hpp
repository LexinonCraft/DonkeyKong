#ifndef GHOST_HPP
#define GHOST_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"
#include "../components/Enemy.hpp"

class Ghost : public BaseEntity, public Updatable, public Enemy {
public:
    enum class State {
        IdleOnPlatform,
        MovingOnPlatform,
        Climbing,
    };
    
    Ghost(Ref ref, std::shared_ptr<Platform> platform, float x_pos);

    void update(float dt, Stage &stage) override;

    bool touches(const sf::RectangleShape &player_shape) const override;

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Component<Updatable>> create_updatable_component() override {
        return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Ghost>(shared_from_this()));
    }

    std::unique_ptr<Component<Enemy>> create_enemy_component() override {
        return std::make_unique<Component<Enemy>>(std::static_pointer_cast<Ghost>(shared_from_this()));
    }

    BaseEntity &get_entity() override {
        return *this;
    }

    sf::Vector2f get_position() const {
        return position;
    }

    bool is_moving_right() const {
        return moving_right;
    }

    void on_hammer_hit() override {
        destroy();
    }

private:
    sf::Vector2f position;
    std::shared_ptr<Platform> current_platform;
    std::shared_ptr<Climbable> current_climbable;
    State state = State::IdleOnPlatform;
    bool moving_right = true;
    bool climbing_up = true;
    float remaining_time = 0.f;
    bool will_climb = false;
    bool just_climbed = false;

    float get_horizontal_speed() const;
};

#endif
