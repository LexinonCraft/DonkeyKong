#ifndef DONKEYKONG_RENDERER_HPP
#define DONKEYKONG_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>

#include "DrawableComponent.hpp"
#include "../model/entities/DonkeyKong.hpp"
#include "AssetsManager.hpp"
#include "../Constants.hpp"
#include "../util/Math.hpp"

/**
 * @brief Renderer for the Donkey Kong entity.
 */
class DonkeyKongRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the Donkey Kong renderer for a concrete entity.
     * @param donkey_kong Donkey Kong instance to render.
     */
    DonkeyKongRenderer(std::shared_ptr<DonkeyKong> donkey_kong, AssetsManager &assets_manager) : donkey_kong(donkey_kong), assets_manager(assets_manager) {}

    /**
     * @brief Draws Donkey Kong into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        AssetsManager::TextureId texture_id;
        bool flip;
        switch (donkey_kong->get_state()) {
            case DonkeyKong::State::Idle:
                texture_id = AssetsManager::TextureId::DonkeyKongStill;
                flip = false;
                break;
            case DonkeyKong::State::ThrowingBarrel:
                switch (mod(floor_to_int(donkey_kong->get_action_timer() / constants::BARREL_THROW_ANIMATION_INTERVAL), 4)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::DonkeyKongThrowingSide;
                        flip = false;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::DonkeyKongThrowingFront;
                        flip = false;
                        break;
                    case 2:
                        texture_id = AssetsManager::TextureId::DonkeyKongThrowingSide;
                        flip = true;
                        break;
                    case 3:
                        texture_id = AssetsManager::TextureId::DonkeyKongStill;
                        flip = false;
                        break;
                    default:
                        throw std::logic_error("Invalid animation frame for Donkey Kong throwing barrel.");
                }
                break;
            case DonkeyKong::State::Angry:
                texture_id = AssetsManager::TextureId::DonkeyKongAngry;
                flip = floor_to_int(donkey_kong->get_action_timer() / constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL) % 2 == 0;
                break;
        }

        sf::Sprite sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y});
        sprite.setPosition(donkey_kong->get_position());
        sprite.setScale({flip ? -2.f : 2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(sprite);
    }

private:
    std::shared_ptr<DonkeyKong> donkey_kong;
    AssetsManager &assets_manager;
};

#endif
