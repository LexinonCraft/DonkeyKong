#include "DK/view/views/StageTransitionView.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/util/Positions.hpp"
#include "DK/view/LayerStack.hpp"

void StageTransitionView::draw() {
    pre_draw();

    sf::Text question_text(assets_manager.get_font());
    question_text.setString("How high can you get?");
    question_text.setCharacterSize(24);
    sf::FloatRect question_bounds = question_text.getLocalBounds();
    question_text.setOrigin({question_bounds.size.x / 2, question_bounds.size.y / 2});
    question_text.setPosition(get_absolute_position({0.f, -50.f}, AnchorPosition::BottomCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(question_text);

    for (unsigned int i = 0; i < stage_in_level + 1; ++i) {
        sf::Sprite donkey_kong_sprite(assets_manager.get_texture(AssetsManager::TextureId::DonkeyKongNice));
        sf::FloatRect donkey_kong_bounds = donkey_kong_sprite.getLocalBounds();
        donkey_kong_sprite.setOrigin({donkey_kong_bounds.size.x / 2, donkey_kong_bounds.size.y / 2});
        donkey_kong_sprite.setPosition(get_absolute_position({0.f, -150.f - i * 100.f}, AnchorPosition::BottomCenter));
        donkey_kong_sprite.setScale({0.7f, 0.7f});
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(donkey_kong_sprite);

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
        stage_text.setCharacterSize(18);
        sf::FloatRect stage_bounds = stage_text.getLocalBounds();
        stage_text.setOrigin({stage_bounds.size.x / 2, stage_bounds.size.y / 2});
        stage_text.setPosition(get_absolute_position({-150.f, -150.f - i * 100.f}, AnchorPosition::BottomCenter));
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(stage_text);
    }

    post_draw();
}
