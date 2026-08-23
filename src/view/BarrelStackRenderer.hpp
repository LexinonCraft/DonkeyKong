#ifndef BARREL_STACK_RENDERER_HPP
#define BARREL_STACK_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include "DK/Constants.hpp"
#include "DK/model/entities/BarrelStack.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the barrel stack entity.
 */
class BarrelStackRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the barrel stack renderer for a concrete entity.
     * @param barrel_stack Barrel stack instance to render.
     */
    BarrelStackRenderer(std::shared_ptr<BarrelStack> barrel_stack, AssetsManager &assets_manager)
        : barrel_stack(barrel_stack), assets_manager(assets_manager) {}

    /**
     * @brief Draws the barrel stack into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        draw_single_barrel(layer_stack, false, false);
        draw_single_barrel(layer_stack, false, true);
        draw_single_barrel(layer_stack, true, false);
        draw_single_barrel(layer_stack, true, true);
    }

private:
    std::shared_ptr<BarrelStack> barrel_stack;
    AssetsManager &assets_manager;

    void draw_single_barrel(LayerStack &layer_stack, bool left, bool bottom) {
        sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelSide1));
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale({constants::BARREL_RADIUS * 2.5f / bounds.size.x, constants::BARREL_RADIUS * 2.5f / bounds.size.y});
        sprite.setOrigin({bounds.size.x, bounds.size.y / 2.f});
        sprite.setRotation(sf::degrees(90));
        auto position = barrel_stack->get_position();
        sprite.setPosition({position.x + (left ? -1.f : 1.f) * constants::BARREL_RADIUS * 2.5f * 5.f / 16.f,
                            position.y + (bottom ? 0.f : -1.f) * constants::BARREL_RADIUS * 2.5f});
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
    }
};

#endif
