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

    bool is_active() const override {
        return true;
    }

    const sf::RectangleShape &get_shape() const {
        return shape;
    }

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    void check_referenced_entities() override {
        if (lower_end->get_entity().is_destroyed() || upper_end->get_entity().is_destroyed()) {
            destroy();
        }
    }

    BaseEntity &get_entity() override { return *this; }

private:
    sf::RectangleShape shape;
};
#endif
