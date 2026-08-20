#ifndef DRAWABLE_COMPONENT_REPOSITORY_HPP
#define DRAWABLE_COMPONENT_REPOSITORY_HPP

#include "DrawableComponent.hpp"
#include "DrawableComponentFactory.hpp"
#include "../model/util/ComponentRepository.hpp"

/**
 * @brief Repository for drawable renderer components used by the view layer.
 */
class DrawableComponentRepository : public ComponentRepository<DrawableComponent> {
public:
    /**
     * @brief Creates a repository for all drawables in the current level.
     * @param entity_repo Entity repository to observe.
     */
    DrawableComponentRepository(EntityRepository &entity_repo, AssetsManager &assets_manager) : ComponentRepository<DrawableComponent>(entity_repo, std::make_unique<DrawableComponentFactory>(assets_manager)) {}

    /**
     * @brief Draws every drawable component onto the active layer stack.
     * @param layer Layer stack receiving the rendered objects.
     */
    void draw_all(LayerStack &layer);

    void update_all(float dt);
};

#endif
