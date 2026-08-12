#ifndef GIRDER_HPP
#define GIRDER_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "../components/Platform.hpp"
#include "../Declarations.hpp"
#include "../util/BaseEntity.hpp"

// A single sloped girder (a tilted floor segment). Defined by its two endpoints
// `left` and `right` (with left.x < right.x). The barrel rolls along its surface.
class Girder : public BaseEntity, public Platform {
public:
    Girder(Ref ref, sf::Vector2f left, sf::Vector2f right);

    // slope = dy/dx = tan(tilt angle); the simple "gravity" approximation
    float slope_at(float x) const override;

    // height (y) of the girder surface at horizontal position x
    float surface_y_at(float x) const override;

    // is x within the girder's horizontal span?
    bool covers_x(float x) const override;

    // direction a barrel rolls along this girder: +1 toward +x, -1 toward -x
    // (always toward the lower end)
    int downhill_sign() const override;

    sf::Vector2f high_end() const override;

    bool is_active() const override;
    sf::Vector2f displacement_at(float x, float dt) const override;

    void accept(EntityVisitor &visitor) override;

    const sf::RectangleShape& get_shape() const;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Platform>> create_platform_component() override {
        return std::make_unique<Component<Platform>>(std::static_pointer_cast<Girder>(shared_from_this()));
    }

private:
    sf::Vector2f left;
    sf::Vector2f right;
    sf::RectangleShape shape;
};

#endif
