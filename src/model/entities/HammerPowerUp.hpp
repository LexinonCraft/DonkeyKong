#ifndef HAMMER_POWER_UP_HPP
#define HAMMER_POWER_UP_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../components/Pickable.hpp"
#include "../util/BaseEntity.hpp"

class HammerPowerUp : public BaseEntity, public Pickable {
public:
    HammerPowerUp(Ref ref, sf::Vector2f position);

    Pickable::Type get_type() const override { return Pickable::Type::Hammer; }

    bool touches(const sf::RectangleShape &player_shape) const override;

    void on_picked_up() override;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Pickable>> create_pickable_component() override {
        return std::make_unique<Component<Pickable>>(std::static_pointer_cast<HammerPowerUp>(shared_from_this()));
    }

    void accept(EntityVisitor &visitor) override;

    sf::Vector2f get_position() const { return position; }

private:
    sf::Vector2f position;
    sf::RectangleShape shape;
};

#endif
