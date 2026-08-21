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
    enum class RenderState {
        Normal,
        StageCompleted,
    };

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
        bool render_barrel = false;
        switch (render_state) {
            case RenderState::Normal:
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
                                render_barrel = true;
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
                        texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
                        flip = floor_to_int(donkey_kong->get_action_timer() / constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL) % 2 == 0;
                        break;
                }
                break;
            case RenderState::StageCompleted:
                if (animation_timer < constants::HEART_BREAKING_DURATION) {
                    texture_id = AssetsManager::TextureId::DonkeyKongStill;
                } else if (animation_timer < constants::HEART_BREAKING_DURATION + constants::DONKEY_KONG_SHOW_TEETH_INTERVAL * constants::DONKEY_KONG_SHOW_TEETH_TIMES * 2) {
                    texture_id = mod(floor_to_int((animation_timer - constants::HEART_BREAKING_DURATION) / constants::DONKEY_KONG_SHOW_TEETH_INTERVAL), 2) == 0 ? AssetsManager::TextureId::DonkeyKongAngry2 : AssetsManager::TextureId::DonkeyKongStill;
                } else {
                    texture_id = AssetsManager::TextureId::DonkeyKongStill;
                }
                flip = false;
                break;
        }

        sf::Sprite donkey_kong_sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect donkey_kong_bounds = donkey_kong_sprite.getLocalBounds();
        donkey_kong_sprite.setOrigin({donkey_kong_bounds.size.x / 2.f, donkey_kong_bounds.size.y});
        donkey_kong_sprite.setPosition(donkey_kong->get_position() + sf::Vector2f{0.f, jump_y_offset});
        donkey_kong_sprite.setScale({flip ? -2.f : 2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(donkey_kong_sprite);

        if (render_barrel) {
            sf::Sprite barrel_sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelSide1));
            sf::FloatRect barrel_bounds = barrel_sprite.getLocalBounds();
            barrel_sprite.setOrigin({barrel_bounds.size.x / 2.f, barrel_bounds.size.y});
            barrel_sprite.setPosition({donkey_kong->get_position().x, donkey_kong->get_position().y - constants::DONKEY_KONG_HOLDED_BARREL_OFFSET_Y});
            barrel_sprite.setScale({constants::BARREL_RADIUS * 2.5f / barrel_bounds.size.x, constants::BARREL_RADIUS * 2.5f / barrel_bounds.size.y});
            layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(barrel_sprite);
        }
    }

    void update(float dt, Stage &stage) override {
        if (stage.get_state() == Stage::StageState::Completed && render_state == RenderState::Normal) {
            animation_timer = 0.0f;
            render_state = RenderState::StageCompleted;
        }

        if (render_state == RenderState::StageCompleted) {
            animation_timer += dt;

            if (animation_timer >= constants::HEART_BREAKING_DURATION && !has_jumped) {
                jump_y_velocity = -constants::DONKEY_KONG_JUMP_SPEED;
                has_jumped = true;
            }

            jump_y_velocity += constants::GRAVITY * dt;
            jump_y_offset += jump_y_velocity * dt;
            if (jump_y_offset > 0.f) {
                jump_y_offset = 0.f;
                jump_y_velocity = 0.f;
            }
        }
    }

private:
    std::shared_ptr<DonkeyKong> donkey_kong;
    AssetsManager &assets_manager;
    RenderState render_state = RenderState::Normal;
    float animation_timer = 0.0f;
    bool has_jumped = false;
    float jump_y_offset = 0.0f;
    float jump_y_velocity = 0.0f;
};

#endif
