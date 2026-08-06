#include "EntityPainter.hpp"
#include "../model/Barrel.hpp"
#include "../model/Player.hpp"
void EntityPainter::visit(const Barrel &barrel) {
    layer.add_to_layer(barrel.get_shape());
}

void EntityPainter::visit(const Player &player) {
    layer.add_to_layer(player.get_shape());
}
