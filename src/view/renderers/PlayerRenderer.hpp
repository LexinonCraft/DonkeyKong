#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/animations/PlayerDeathAnimation.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the player entity.
 */
class PlayerRenderer : public DrawableComponent {
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

    /**
     * @brief Internal animation visitor for handling player animations.
     */
    class PlayerAnimationVisitor : public AnimationVisitor {
    public:
        AssetsManager::TextureId texture_id;
        bool flip_sprite = false;
        bool rotate_sprite = false;
        bool render_player = true;

        void visit(PlayerDeathAnimation &animation) override;

        void visit(Stage100MCompletionAnimation &animation) override;
    };
};

#endif
