#ifndef BARREL_STACK_HPP
#define BARREL_STACK_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/util/BaseEntity.hpp"
#include "DK/model/util/EntityVisitor.hpp"

class BarrelStack : public BaseEntity {
public:
    BarrelStack(Ref ref, std::shared_ptr<Platform> platform, float x_position)
        : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

    void accept(EntityVisitor &visitor) override { visitor.visit(*this); }

    sf::Vector2f get_position() const { return position; }

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f position;
};

#endif
