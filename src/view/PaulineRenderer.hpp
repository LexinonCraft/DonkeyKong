#ifndef PAULINE_RENDERER_HPP
#define PAULINE_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>
#include <stdexcept>

#include "DrawableComponent.hpp"
#include "../model/entities/Pauline.hpp"
#include "AssetsManager.hpp"
#include "../Constants.hpp"
#include "../util/Math.hpp"
#include "LayerStack.hpp"

/**
 * @brief Renderer for the Pauline entity.
 */
class PaulineRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the Pauline renderer for a concrete entity.
     * @param pauline Pauline instance to render.
     */
    PaulineRenderer(std::shared_ptr<Pauline> pauline, AssetsManager &assets_manager) : pauline(pauline), assets_manager(assets_manager) {}

    /**
     * @brief Draws Pauline into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        AssetsManager::TextureId texture_id;
        bool help;
        float animation_timer = pauline->get_animation_timer();
        if (animation_timer < constants::PAULINE_SCREAM_ANIMATION_INTERVAL * constants::PAULINE_SCREAM_ANIMATION_FRAMES) {
            switch (mod(floor_to_int(animation_timer / constants::PAULINE_SCREAM_ANIMATION_INTERVAL), 2)) {
                case 0:
                    texture_id = AssetsManager::TextureId::PaulineScream1;
                    break;
                case 1:
                    texture_id = AssetsManager::TextureId::PaulineScream2;
                    break;
                default:
                    throw std::logic_error("Invalid animation frame for Pauline's scream animation.");
            }
            help = true;
        } else {
            texture_id = AssetsManager::TextureId::PaulineStill;
            help = false;
        }

        sf::Sprite pauline_sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect bounds = pauline_sprite.getLocalBounds();
        pauline_sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y});
        auto position = pauline->get_position();
        pauline_sprite.setPosition({position.x, position.y + bounds.size.y / 32.f * 5.f});
        pauline_sprite.setScale({2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(pauline_sprite);

        if (help) {
            sf::Sprite help_sprite(assets_manager.get_texture(AssetsManager::TextureId::Help));
            sf::FloatRect help_bounds = help_sprite.getLocalBounds();
            help_sprite.setOrigin({help_bounds.size.x / 2.f, help_bounds.size.y});
            help_sprite.setPosition({position.x + 40.f, position.y - 40.f});
            help_sprite.setScale({2.f, 2.f});
            layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(help_sprite);
        }
    }

private:
    std::shared_ptr<Pauline> pauline;
    AssetsManager &assets_manager;
};

#endif
