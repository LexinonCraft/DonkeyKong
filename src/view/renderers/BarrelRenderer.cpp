#include "DK/view/renderers/BarrelRenderer.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/entities/Barrel.hpp"
#include "DK/util/Math.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void BarrelRenderer::draw(LayerStack &layer_stack) {
    AssetsManager::TextureId texture_id;
    bool rotate_sprite;
    switch (barrel->get_state()) {
        case Barrel::State::OnGirder:
        case Barrel::State::Falling:
            {
                switch (mod(floor_to_int(-barrel->get_roll_distance()), constants::BARREL_FRONT_ANIMATION_FRAME_COUNT)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::BarrelFront1;
                        rotate_sprite = false;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::BarrelFront2;
                        rotate_sprite = false;
                        break;
                    case 2:
                        texture_id = AssetsManager::TextureId::BarrelFront1;
                        rotate_sprite = true;
                        break;
                    case 3:
                        texture_id = AssetsManager::TextureId::BarrelFront2;
                        rotate_sprite = true;
                        break;
                    default:
                        throw std::logic_error("Unexpected roll distance modulo value for barrel rendering.");
                        break;
                }
                break;
            }
        case Barrel::State::RollingDownClimbable:
            {
                switch (mod(floor_to_int(barrel->get_roll_distance()), 2)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::BarrelSide1;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::BarrelSide2;
                        break;
                    default:
                        throw std::logic_error("Unexpected roll distance modulo value for barrel rendering.");
                        break;
                }
                rotate_sprite = false;
                break;
            }
    }

    sf::Sprite sprite(assets_manager.get_texture(texture_id));
    sf::FloatRect sprite_bounds = sprite.getLocalBounds();
    sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
    sprite.setScale({constants::BARREL_RADIUS * constants::BARREL_RENDER_SIZE_FACTOR / sprite_bounds.size.x,
                     constants::BARREL_RADIUS * constants::BARREL_RENDER_SIZE_FACTOR / sprite_bounds.size.y});
    if (rotate_sprite) {
        sprite.setRotation(sf::degrees(constants::HALF_TURN_DEGREES));
    }
    sf::Vector2f barrel_position = barrel->get_position();
    sprite.setPosition({barrel_position.x, barrel_position.y - constants::BARREL_RADIUS * constants::BARREL_RENDER_SIZE_FACTOR *
                                                                   constants::BARREL_RENDER_VERTICAL_OFFSET_FACTOR});

    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
}
