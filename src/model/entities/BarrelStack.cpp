#include "DK/model/entities/BarrelStack.hpp"

#include "DK/model/components/Platform.hpp"
#include "DK/model/util/EntityVisitor.hpp"

BarrelStack::BarrelStack(Ref ref, std::shared_ptr<Platform> platform, float x_position)
    : BaseEntity(ref), position({x_position, platform->surface_y_at(x_position)}) {}

void BarrelStack::accept(EntityVisitor &visitor) { visitor.visit(*this); }
