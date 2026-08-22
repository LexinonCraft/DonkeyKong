#ifndef DONKEYKONG_RENDERER_HPP
#define DONKEYKONG_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>

#include "DK/Constants.hpp"
#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/util/Math.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the Donkey Kong entity.
 */
class DonkeyKongRenderer : public DrawableComponent, private AnimationVisitor {
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
    AssetsManager::TextureId texture_id;
    bool flip;
    bool render_barrel;

    void visit(Stage25MCompletionAnimation &animation) override {
        flip = false;
        switch (animation.get_state()) {
            case Stage25MCompletionAnimation::State::NotStarted:
            case Stage25MCompletionAnimation::State::United:
                texture_id = AssetsManager::TextureId::DonkeyKongStill;
                break;
            case Stage25MCompletionAnimation::State::Climbing:
            case Stage25MCompletionAnimation::State::Finished:
                texture_id =
                    mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_CLIMBING_FRAME_INTERVAL), 2) == 0
                        ? AssetsManager::TextureId::DonkeyKongClimbing1
                        : AssetsManager::TextureId::DonkeyKongClimbing2;
                break;
        }
    }

    void visit(Stage100MCompletionAnimation &animation) override {
        flip = false;
        switch (animation.get_state()) {
            case Stage100MCompletionAnimation::State::NotStarted:
                texture_id = AssetsManager::TextureId::DonkeyKongStill;
                break;
            case Stage100MCompletionAnimation::State::BeforeFall:
                texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
                flip = mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_BEFORE_FALL_FRAME_INTERVAL), 2) == 0;
                break;
            case Stage100MCompletionAnimation::State::Falling:
                texture_id = AssetsManager::TextureId::DonkeyKongFalling1;
                break;
            case Stage100MCompletionAnimation::State::Impact:
                texture_id = AssetsManager::TextureId::DonkeyKongFalling2;
                break;
            case Stage100MCompletionAnimation::State::United:
            case Stage100MCompletionAnimation::State::Finished:
                switch (mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_AFTER_FALL_FRAME_INTERVAL), 3)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::DonkeyKongFalling1;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::DonkeyKongFalling2;
                        break;
                    case 2:
                        texture_id = AssetsManager::TextureId::DonkeyKongFalling3;
                        break;
                }
                break;
        }
    }
};

#endif
