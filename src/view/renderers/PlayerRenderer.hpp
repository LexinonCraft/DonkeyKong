#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DK/Constants.hpp"
#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/animations/PlayerDeathAnimation.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/util/Math.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the player entity.
 */
class PlayerRenderer : public DrawableComponent, private AnimationVisitor {
public:
    /**
     * @brief Creates the player renderer for a concrete entity.
     * @param player Player instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    PlayerRenderer(std::shared_ptr<Player> player, AssetsManager &assets_manager) : player(player), assets_manager(assets_manager) {}

    /**
     * @brief Draws the player into the player layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<Player> player;
    AssetsManager &assets_manager;
    AssetsManager::TextureId texture_id;
    bool flip_sprite = false;
    bool rotate_sprite = false;
    bool hammer_origin = false;
    bool render_player = true;

    void visit(PlayerDeathAnimation &animation) override {
        switch (animation.get_state()) {
            case PlayerDeathAnimation::State::NotStarted:
            case PlayerDeathAnimation::State::BeforeRotating:
                texture_id = AssetsManager::TextureId::JumpmanDying1;
                rotate_sprite = false;
                break;
            case PlayerDeathAnimation::State::Rotating:
                switch (mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::PLAYER_DYING_ANIMATION_INTERVAL), 4)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::JumpmanDying1;
                        rotate_sprite = false;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::JumpmanDying2;
                        rotate_sprite = false;
                        break;
                    case 2:
                        texture_id = AssetsManager::TextureId::JumpmanDying1;
                        rotate_sprite = true;
                        break;
                    case 3:
                        texture_id = AssetsManager::TextureId::JumpmanDying2;
                        rotate_sprite = true;
                        break;
                }
                break;
            case PlayerDeathAnimation::State::AfterRotating:
            case PlayerDeathAnimation::State::Finished:
                texture_id = AssetsManager::TextureId::JumpmanDead;
                rotate_sprite = false;
                break;
        }
        flip_sprite = false;
        hammer_origin = false;
    }

    void visit(Stage100MCompletionAnimation &animation) override {
        switch (animation.get_state()) {
            case Stage100MCompletionAnimation::State::NotStarted:
            case Stage100MCompletionAnimation::State::BeforeFall:
            case Stage100MCompletionAnimation::State::Falling:
            case Stage100MCompletionAnimation::State::Impact:
                render_player = false;
                break;
            case Stage100MCompletionAnimation::State::United:
            case Stage100MCompletionAnimation::State::Finished:
                texture_id = AssetsManager::TextureId::JumpmanStill;
                flip_sprite = true;
                break;
        }
    }
};

#endif
