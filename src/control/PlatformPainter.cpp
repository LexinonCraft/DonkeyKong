#include "PlatformPainter.hpp"
#include "../model/Girder.hpp"

void PlatformPainter::visit(const Girder &girder) {
    layer.add_to_layer(girder.get_shape());
}
