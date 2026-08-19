#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "StageTransitionView.hpp"
#include "../util/Positions.hpp"
#include "../model/StageSequence.hpp"

void StageTransitionView::draw() {
    pre_draw();

    std::string stage_label;
    switch (get_stage_id(player_data)) {
        case StageId::Stage25M:
            stage_label = "25M";
            break;
        case StageId::Stage50M:
            stage_label = "50M";
            break;
        case StageId::Stage75M:
            stage_label = "75M";
            break;
        case StageId::Stage100M:
            stage_label = "100M";
            break;
    }

    sf::Text title(assets_manager.get_font());
    title.setString("How high can you go? (" + stage_label + ")");
    title.setCharacterSize(18);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    post_draw();
}
