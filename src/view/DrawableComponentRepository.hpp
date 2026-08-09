#ifndef DRAWABLE_COMPONENT_REPOSITORY_H
#define DRAWABLE_COMPONENT_REPOSITORY_H

#include "DrawableComponent.hpp"
#include "DrawableComponentFactory.hpp"
#include "../model/util/ComponentRepository.hpp"

class DrawableComponentRepository : public ComponentRepository<DrawableComponent> {
public:
    DrawableComponentRepository(EntityRepository &entity_repo) : ComponentRepository<DrawableComponent>(entity_repo, std::make_unique<DrawableComponentFactory>()) {}

    void draw_all(LayerStack &layer) {
        for (auto it = begin(); it != end(); ++it) {
            it->second->draw(layer);
        }
    }
};

#endif
