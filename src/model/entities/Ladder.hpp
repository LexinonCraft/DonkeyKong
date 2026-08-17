#ifndef LADDER_HPP
#define LADDER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "../components/Platform.hpp"
#include "../components/Climbable.hpp"
#include "../util/BaseEntity.hpp"

/// @brief Represents a ladder connecting two girders at a specific x position.
class Ladder : public BaseEntity, public Climbable {
public:
    Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos);

    bool is_active_for_player() const override {
        return true;
    }

    const sf::RectangleShape &get_shape() const {
        return shape;
    }

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    void check_referenced_entities() override;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Climbable>> create_climbable_component() override {
        return std::make_unique<Component<Climbable>>(std::static_pointer_cast<Ladder>(shared_from_this()));
    }

private:
    sf::RectangleShape shape;
};
#endif
