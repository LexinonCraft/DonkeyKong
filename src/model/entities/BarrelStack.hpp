#ifndef BARREL_STACK_HPP
#define BARREL_STACK_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Decorative stack of barrels positioned on a platform.
 */
class BarrelStack : public BaseEntity {
public:
    BarrelStack(Ref ref, std::shared_ptr<Platform> platform, float x_position);

    void accept(EntityVisitor &visitor) override;

    sf::Vector2f get_position() const { return position; }

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f position;
};

#endif
