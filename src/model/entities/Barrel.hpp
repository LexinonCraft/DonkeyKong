#ifndef BARREL_HPP
#define BARREL_HPP

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Declarations.hpp"
#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"
#include "../components/Enemy.hpp"

/**
 * @brief Barrel entity that rolls down sloped platforms and falls between them.
 *
 * The barrel is a small two-state simulation: it either sticks to a platform and
 * rolls downhill, or it is in free fall until it intersects another platform.
 */
class Barrel : public BaseEntity, public Updatable, public Enemy {
public:
    /**
     * @brief Current barrel state.
     */
    enum class State { OnGirder, Falling, RollingDownClimbable };

    /**
     * @brief Creates a barrel at a world position.
     * @param ref Repository reference assigned to the barrel.
     * @param position Initial world position.
     */
    Barrel(Ref ref, sf::Vector2f position);

    /**
     * @brief Places the barrel on a platform and sets its rolling direction.
     * @param platform Platform surface to rest on.
     */
    void set_on_platform(std::shared_ptr<Platform> platform);

    /**
     * @brief Advances the barrel simulation by one time step.
     * @param dt Time step in seconds.
     * @param level Level used to resolve platform intersections.
     */
    void update(float dt, Stage &level) override;

    /**
     * @brief Returns whether the barrel is currently attached to a platform.
     * @return OnGirder if attached, otherwise Falling.
     */
    State get_state() const { return state; }

    /**
     * @brief Returns the barrel's world position.
     * @return Current position vector.
     */
    sf::Vector2f get_position() const { return position; }

    /**
     * @brief Returns the current horizontal velocity.
     * @return x-velocity in pixels per second.
     */
    float get_vx() const { return vx; }

    /**
     * @brief Returns the current vertical velocity.
     * @return y-velocity in pixels per second.
     */
    float get_vy() const { return vy; }

    /**
     * @brief Returns the barrel's SFML render shape.
     * @return Circle shape used for rendering.
     */
    const sf::CircleShape &get_shape() const { return shape; }

    /**
     * @brief Dispatches the barrel to the visitor.
     * @param visitor Visitor used for object-specific rendering logic.
     */
    void accept(EntityVisitor &visitor) override;

    /**
     * @brief Clears references to deleted platforms.
     */
    void check_referenced_entities() override;

    /**
     * @brief Returns the underlying entity as an abstract base pointer.
     * @return Reference to this entity.
     */
    BaseEntity &get_entity() override { return *this; }

    /**
     * @brief Creates the updatable component for this barrel.
     * @return Unique pointer to the component wrapper.
     */
    std::unique_ptr<Component<Updatable>> create_updatable_component() override {
        return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Barrel>(shared_from_this()));
    }

    std::unique_ptr<Component<Enemy>> create_enemy_component() override {
        return std::make_unique<Component<Enemy>>(std::static_pointer_cast<Barrel>(shared_from_this()));
    }

    bool touches(const sf::RectangleShape &player_shape) const override;

    float get_roll_distance() const { return roll_distance; }

private:
    sf::Vector2f position;
    float vx = 0.f;
    float vy = 0.f;

    State state = State::Falling;
    std::shared_ptr<Platform> current_platform = nullptr;
    std::shared_ptr<Climbable> current_climbable = nullptr;
    bool roll_down_climbable;
    float roll_distance = 0.f;
    
    sf::CircleShape shape;

    /**
     * @brief Snaps the barrel onto a platform if it intersects the platform surface.
     * @param platforms Repository of all platform objects in the level.
     */
    void check_platform_intersection(PlatformComponentRepository &platforms, float dt);

    float platform_h_tolerance_left() const;
    float platform_h_tolerance_right() const;
    float platform_snap_distance(float dt) const;
};

#endif
