#include "DK/view/renderers/LadderRenderer.hpp"

void LadderRenderer::draw(LayerStack &layer_stack) {
    if (ladder->is_broken()) {
        float midway_y = (ladder->get_lower_y_pos() + ladder->get_upper_y_pos()) / 2.f;
        draw_raw(ladder->get_x_pos(), ladder->get_lower_y_pos(), midway_y + 10.f, layer_stack);
        draw_raw(ladder->get_x_pos(), midway_y - 10.f, ladder->get_upper_y_pos() + 5.f, layer_stack);
    } else {
        draw_raw(ladder->get_x_pos(), ladder->get_lower_y_pos(), ladder->get_upper_y_pos() + 5.f, layer_stack);
    }
}

void LadderRenderer::draw_raw(float x, float lower_y, float upper_y, LayerStack &layer_stack) {
    float y_diff = lower_y - upper_y;
    int num_tiles = static_cast<int>(y_diff / 20.f);
    float tile_height = y_diff / num_tiles;

    AssetsManager::TextureId texture_id;
    switch (ladder->get_color()) {
        case Ladder::Color::Cyan:
            texture_id = AssetsManager::TextureId::LadderCyan;
            break;
        case Ladder::Color::Yellow:
            texture_id = AssetsManager::TextureId::LadderYellow;
            break;
    }

    for (int i = 0; i < num_tiles; ++i) {
        sf::Sprite sprite(assets_manager.get_texture(texture_id));
        sprite.setPosition({x, upper_y + i * tile_height});
        auto sprite_bounds = sprite.getLocalBounds();
        sprite.setScale({20.f / sprite_bounds.size.x, tile_height / sprite_bounds.size.y});
        sprite.setOrigin({sprite_bounds.size.x / 2.f, 0.f});
        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(sprite);
    }
}
