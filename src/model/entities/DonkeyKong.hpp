#ifndef DONKEYKONG_HPP
#define DONKEYKONG_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"
#include "../components/Enemy.hpp"
#include "../util/EntityVisitor.hpp"
#include "../Declarations.hpp"

class DonkeyKong : public BaseEntity, public Updatable, public Enemy {
public:
    enum class State {
        Idle,
        ThrowingBarrel,
        Angry,
    };

    DonkeyKong(Ref ref, std::shared_ptr<Platform> platform, float x_position, bool throw_barrels);

    void update(float dt, Stage &stage) override;

    bool touches(const sf::RectangleShape &player_shape) const override;

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    std::unique_ptr<Component<Updatable>> create_updatable_component() override {
        return std::make_unique<Component<Updatable>>(std::static_pointer_cast<DonkeyKong>(shared_from_this()));
    }

    std::unique_ptr<Component<Enemy>> create_enemy_component() override {
        return std::make_unique<Component<Enemy>>(std::static_pointer_cast<DonkeyKong>(shared_from_this()));
    }

    BaseEntity &get_entity() override {
        return *this;
    }

    sf::Vector2f get_position() const {
        return position;
    }

    State get_state() const {
        return state;
    }

    float get_idle_countdown() const {
        return idle_countdown;
    }

    float get_action_timer() const {
        return action_timer;
    }

private:
    sf::Vector2f position;
    std::shared_ptr<Platform> platform;
    float action_timer = 0.f;
    unsigned int num_barrels_to_be_thrown = 0;
    unsigned int angry_animation_frames = 0;
    float idle_countdown = 0.f;
    State state = State::Idle;
    unsigned int consecutive_angry_actions = 0;

    bool throw_barrels;

    void switch_to_idle(int random_int);
};

#endif
