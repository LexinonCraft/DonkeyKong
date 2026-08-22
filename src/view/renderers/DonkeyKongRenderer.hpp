#ifndef DONKEYKONG_RENDERER_HPP
#define DONKEYKONG_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>

#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the Donkey Kong entity.
 */
class DonkeyKongRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the Donkey Kong renderer for a concrete entity.
     * @param donkey_kong Donkey Kong instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    DonkeyKongRenderer(std::shared_ptr<DonkeyKong> donkey_kong, AssetsManager &assets_manager)
        : donkey_kong(donkey_kong), assets_manager(assets_manager) {}

    /**
     * @brief Draws Donkey Kong into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<DonkeyKong> donkey_kong;
    AssetsManager &assets_manager;

    /**
     * @brief Internal animation visitor class for handling Donkey Kong's animations.
     */
    class DonkeyKongAnimationVisitor : public AnimationVisitor {
    public:
        AssetsManager::TextureId texture_id;
        bool flip = false;

        void visit(Stage25MCompletionAnimation &animation) override;

        void visit(Stage100MCompletionAnimation &animation) override;
    };
};

#endif
