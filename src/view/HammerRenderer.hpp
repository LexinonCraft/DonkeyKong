#ifndef HAMMER_RENDERER_HPP
#define HAMMER_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "../model/entities/HammerPowerUp.hpp"
#include "AssetsManager.hpp"
#include "DrawableComponent.hpp"

class HammerRenderer : public DrawableComponent {
public:
    HammerRenderer(std::shared_ptr<HammerPowerUp> hammer, AssetsManager &assets_manager) : hammer(hammer), assets_manager(assets_manager) {}

    void draw(LayerStack &layer_stack) override {
        sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
        sprite.setOrigin({8.f, 16.f});
        sprite.setPosition(hammer->get_position());
        sprite.setScale({2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
    }

private:
    std::shared_ptr<HammerPowerUp> hammer;
    AssetsManager &assets_manager;
};

#endif
