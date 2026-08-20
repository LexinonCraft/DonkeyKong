#ifndef PAULINE_HPP
#define PAULINE_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "../util/BaseEntity.hpp"
#include "../util/EntityVisitor.hpp"
#include "../Declarations.hpp"
#include "../components/Platform.hpp"
#include "../components/Updatable.hpp"
#include "../../Constants.hpp"

class Pauline : public BaseEntity, public Updatable {
public:
    Pauline(Ref ref, std::shared_ptr<Platform> platform, float x_position) : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    sf::Vector2f get_position() const {
        return position;
    }

    float get_animation_timer() const {
        return animation_timer;
    }

    void update(float dt, Stage &stage) override {
        animation_timer += dt;
        if (animation_timer > constants::PAULINE_ANIMATION_LENGTH) {
            animation_timer -= constants::PAULINE_ANIMATION_LENGTH;
        }
    }

    BaseEntity &get_entity() override {
        return *this;
    }

    std::unique_ptr<Component<Updatable>> create_updatable_component() override {
        return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Pauline>(shared_from_this()));
    }

private:
    sf::Vector2f position;
    float animation_timer = 0.0f;
};

#endif
