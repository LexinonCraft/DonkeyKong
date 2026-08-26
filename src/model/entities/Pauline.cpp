#include "DK/model/entities/Pauline.hpp"

#include "DK/model/components/Platform.hpp"
#include "DK/model/util/EntityVisitor.hpp"

Pauline::Pauline(Ref ref, std::shared_ptr<Platform> platform, float x_position)
    : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

void Pauline::accept(EntityVisitor &visitor) { visitor.visit(*this); }

void Pauline::start_animation(AbstractAnimation *animation) {
    current_animation = animation;
    set_state(State::Animated);
}

void Pauline::stop_animation() {
    current_animation = nullptr;
    set_state(State::Normal);
}
