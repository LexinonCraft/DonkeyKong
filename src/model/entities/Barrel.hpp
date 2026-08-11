#ifndef BARREL_HPP
#define BARREL_HPP

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Declarations.hpp"
#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"

// A barrel rolling down the girders. It is a tiny 2-state machine:
//  - OnGirder: glued to the girder surface, rolling downhill at constant speed
//              (the simple tan(angle) "gravity on a slope" approximation).
//  - Falling:  in the air between girders, pulled down by gravity (vy += g*dt),
//              until it crosses the surface of the girder below.
class Barrel : public BaseEntity, public Updatable {
public:
    enum class State { OnGirder, Falling };

    Barrel(Ref ref, sf::Vector2f position);

    // place the barrel on `girder`, rolling toward its lower end
    void set_on_platform(std::shared_ptr<Platform> platform);

    // advance the physics by `dt` seconds, given the stage's platforms
    void update(float dt, Level &level) override;

    // Falling iff we are not currently resting on a girder
    State get_state() const { return current_platform ? State::OnGirder : State::Falling; }
    sf::Vector2f get_position() const { return position; }
    float get_vx() const { return vx; }
    float get_vy() const { return vy; }
    const sf::CircleShape &get_shape() const { return shape; }

    void accept(EntityVisitor &visitor) override;

    void check_referenced_entities() override;

    BaseEntity &get_entity() override { return *this; }

private:
    // if a platform surface lies within the barrel's lower half, snap onto it
    void check_platform_intersection(PlatformComponentRepository &platforms);

    sf::Vector2f position;
    float vx = 0.f;
    float vy = 0.f;

    // the girder we are rolling on, or empty while falling.
    std::shared_ptr<Platform> current_platform = nullptr;

    sf::CircleShape shape;
};

#endif
