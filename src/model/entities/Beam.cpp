#include "DK/model/entities/Beam.hpp"

#include "DK/model/components/Platform.hpp"
#include "DK/model/util/EntityVisitor.hpp"

Beam::Beam(Ref ref, std::shared_ptr<Platform> lower_platform, std::shared_ptr<Platform> upper_platform, float x_position)
    : BaseEntity(ref), x(x_position), lower_y(lower_platform->surface_y_at(x_position)),
      upper_y(upper_platform->surface_y_at(x_position)) {}

void Beam::accept(EntityVisitor &visitor) { visitor.visit(*this); }
