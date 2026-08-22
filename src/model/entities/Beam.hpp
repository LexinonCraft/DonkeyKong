#ifndef BEAM_HPP
#define BEAM_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "DK/model/util/BaseEntity.hpp"
#include "DK/model/util/EntityVisitor.hpp"
#include "DK/model/Declarations.hpp"
#include "DK/model/components/Platform.hpp"

class Beam : public BaseEntity {
public:
    Beam(Ref ref, std::shared_ptr<Platform> lower_platform, std::shared_ptr<Platform> upper_platform, float x_position) 
        : BaseEntity(ref), x(x_position), lower_y(lower_platform->surface_y_at(x_position)), upper_y(upper_platform->surface_y_at(x_position)) {}

    void accept(EntityVisitor &visitor) override {
        visitor.visit(*this);
    }

    float get_x() const {
        return x;
    }

    float get_lower_y() const {
        return lower_y;
    }

    float get_upper_y() const {
        return upper_y;
    }

private:
    float x;
    float lower_y;
    float upper_y;
};

#endif
