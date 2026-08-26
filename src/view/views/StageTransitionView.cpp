#include "DK/view/views/StageTransitionView.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void StageTransitionView::draw() {
    pre_draw();

    // "How high can you get?" text
    sf::Text question_text(assets_manager.get_font());
    question_text.setString("How high can you get?");
    question_text.setCharacterSize(constants::TEXT_CHARACTER_SIZE);
    set_origin(question_text, AnchorPosition::Center);
    question_text.setPosition(get_absolute_position({0.f, constants::STAGE_TRANSITION_QUESTION_Y}, AnchorPosition::BottomCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(question_text);

    for (unsigned int i = 0; i < stage_in_level + 1; ++i) {
        // Donkey Kong sprite
        sf::Sprite donkey_kong_sprite(assets_manager.get_texture(AssetsManager::TextureId::DonkeyKongNice));
        set_origin(donkey_kong_sprite, AnchorPosition::Center);
        const float row_y = constants::STAGE_TRANSITION_ROW_START_Y - i * constants::STAGE_TRANSITION_ROW_SPACING;
        donkey_kong_sprite.setPosition(get_absolute_position({0.f, row_y}, AnchorPosition::BottomCenter));
        scale(donkey_kong_sprite, constants::STAGE_TRANSITION_DONKEY_KONG_SCALE);
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(donkey_kong_sprite);

        // Stage text
        sf::Text stage_text(assets_manager.get_font());
        std::string stage_string;
        switch ((*stage_sequence)[i]) {
            case StageId::Stage25M:
                stage_string = "25 m";
                break;
            case StageId::Stage100M:
                stage_string = "100 m";
                break;
        }
        stage_text.setString(stage_string);
        stage_text.setCharacterSize(constants::STAGE_TRANSITION_STAGE_CHARACTER_SIZE);
        set_origin(stage_text, AnchorPosition::Center);
        stage_text.setPosition(get_absolute_position({constants::STAGE_TRANSITION_STAGE_TEXT_X, row_y}, AnchorPosition::BottomCenter));
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(stage_text);
    }

    post_draw();
}
