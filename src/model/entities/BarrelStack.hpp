#ifndef BARREL_STACK_HPP
#define BARREL_STACK_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "../util/BaseEntity.hpp"
#include "../util/EntityVisitor.hpp"
#include "../Declarations.hpp"
#include "../components/Platform.hpp"

class BarrelStack : public BaseEntity {
public:
    enum class State {
        Idle,
        ThrowingBarrel,
        Angry,
    };

    BarrelStack(Ref ref, std::shared_ptr<Platform> platform, float x_position) : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    sf::Vector2f get_position() const {
        return position;
    }

private:
    sf::Vector2f position;
};

#endif
