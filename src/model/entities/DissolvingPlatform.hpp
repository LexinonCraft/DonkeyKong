#ifndef DISSOLVING_PLATFORM_HPP
#define DISSOLVING_PLATFORM_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Horizontal platform that dissolves after the player crosses its center.
 *
 * Once its dissolve timer finishes, the platform lets the player fall through it.
 */
class DissolvingPlatform : public BaseEntity, public Platform, public Updatable {
public:
    /**
     * @brief Creates a dissolving platform at the specified position with the given width.
     * @param ref Repository reference assigned to the platform.
     * @param position World-space position of the platform.
     * @param width Width of the platform.
     */
    DissolvingPlatform(Ref ref, sf::Vector2f position, float width);

    float slope_at(float x) const override;

    float surface_y_at(float x) const override;

    bool covers_x(float x, float h_tolerance_left, float h_tolerance_right) const override;

    int downhill_sign() const override;

    sf::Vector2f high_end() const override;

    bool is_active() const override;

    sf::Vector2f displacement_at(float x, float dt) const override;

    void accept(EntityVisitor &visitor) override;

    BaseEntity &get_entity() override { return *this; }

    sf::Vector2f get_position() const { return position; }

    float get_width() const { return width; }

    void update(float dt, Stage &stage) override;

    std::unique_ptr<Component<Platform>> create_platform_component() override;

    std::unique_ptr<Component<Updatable>> create_updatable_component() override;

    bool fall_through(std::shared_ptr<Player> player) override;

    bool has_dissolved() const;

private:
    sf::Vector2f position;
    float width;
    bool is_dissolving = false;
    bool dissolved = false;
    float dissolve_timer = 0.f;
};

#endif
