#include "DK/model/entities/DissolvingPlatform.hpp"

#include "DK/Constants.hpp"
#include "DK/model/Stage.hpp"
#include "DK/model/entities/Player.hpp"

DissolvingPlatform::DissolvingPlatform(Ref ref, sf::Vector2f position, float width) : BaseEntity(ref), position(position), width(width) {}

float DissolvingPlatform::slope_at(float x) const { return 0.f; }

float DissolvingPlatform::surface_y_at(float x) const { return position.y; }

bool DissolvingPlatform::covers_x(float x, float h_tolerance_left, float h_tolerance_right) const {
    return x >= position.x - width / 2.f - h_tolerance_left && x <= position.x + width / 2.f + h_tolerance_right;
}

int DissolvingPlatform::downhill_sign() const { return 0; }

sf::Vector2f DissolvingPlatform::high_end() const {
    // the upper end has the smaller y
    return position; // for a horizontal platform, both ends have the same y
}

bool DissolvingPlatform::is_active() const { return true; }

sf::Vector2f DissolvingPlatform::displacement_at(float x, float dt) const {
    // the platform is static, so no displacement
    return {0.f, 0.f};
}

void DissolvingPlatform::accept(EntityVisitor &visitor) { visitor.visit(*this); }

void DissolvingPlatform::update(float dt, Stage &stage) {
    if (is_dissolving) {
        if (dissolve_timer < constants::DISSOLVING_PLATFORM_DISSOLVE_DURATION) {
            dissolve_timer += dt;
        }
        if (dissolve_timer >= constants::DISSOLVING_PLATFORM_DISSOLVE_DURATION && !dissolved) {
            dissolved = true;
            stage.add_to_score(position, constants::DISSOLVING_PLATFORM_SCORE);
        }
    }
}

std::unique_ptr<Component<Platform>> DissolvingPlatform::create_platform_component() {
    return std::make_unique<Component<Platform>>(std::static_pointer_cast<DissolvingPlatform>(shared_from_this()));
}

std::unique_ptr<Component<Updatable>> DissolvingPlatform::create_updatable_component() {
    return std::make_unique<Component<Updatable>>(std::static_pointer_cast<DissolvingPlatform>(shared_from_this()));
}

bool DissolvingPlatform::fall_through(std::shared_ptr<Player> player) {
    float player_x_pos = player->get_position().x;
    if (!is_dissolving && covers_x(player_x_pos, -constants::DISSOLVING_PLATFORM_DISSOLVE_H_TOLERANCE,
                                   -constants::DISSOLVING_PLATFORM_DISSOLVE_H_TOLERANCE)) {
        is_dissolving = true;
        dissolve_timer = 0.f;
    }
    return has_dissolved() && covers_x(player_x_pos, -constants::DISSOLVING_PLATFORM_FALL_THROUGH_H_TOLERANCE,
                                       -constants::DISSOLVING_PLATFORM_FALL_THROUGH_H_TOLERANCE);
}

bool DissolvingPlatform::has_dissolved() const { return dissolved; }
