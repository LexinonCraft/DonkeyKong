#ifndef BARREL_RENDERER_HPP
#define BARREL_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Barrel.hpp"
#include "AssetsManager.hpp"
#include "../Constants.hpp"
#include "../util/Math.hpp"
#include <SFML/Graphics/Rect.hpp>

/**
 * @brief Renderer for the barrel entity.
 */
class BarrelRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the barrel renderer for a concrete entity.
     * @param barrel Barrel instance to render.
     */
    BarrelRenderer(std::shared_ptr<Barrel> barrel, AssetsManager &assets_manager) : barrel(barrel), assets_manager(assets_manager) {}

    /**
     * @brief Draws the barrel into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        AssetsManager::TextureId texture_id;
        bool rotate_sprite;
        switch (barrel->get_state()) {
            case Barrel::State::OnGirder:
            case Barrel::State::Falling: {
                switch (mod(floor_to_int(-barrel->get_roll_distance()), 4)) {
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
            case Barrel::State::RollingDownClimbable: {
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
        sprite.setScale({constants::BARREL_RADIUS * 2.5f / sprite_bounds.size.x, constants::BARREL_RADIUS * 2.5f / sprite_bounds.size.y});
        if (rotate_sprite) {
            sprite.setRotation(sf::degrees(180.f));
        }
        sf::Vector2f barrel_position = barrel->get_position();
        sprite.setPosition({barrel_position.x, barrel_position.y - constants::BARREL_RADIUS * 2.5f * 5.f / 16.f});

        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
    }

private:
    std::shared_ptr<Barrel> barrel;
    AssetsManager &assets_manager;
};

#endif
