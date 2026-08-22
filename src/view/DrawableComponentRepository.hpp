#ifndef DRAWABLE_COMPONENT_REPOSITORY_HPP
#define DRAWABLE_COMPONENT_REPOSITORY_HPP

#include "DK/model/util/ComponentRepository.hpp"
#include "DK/view/DrawableComponent.hpp"
#include "DK/view/DrawableComponentFactory.hpp"

/**
 * @brief Repository for drawable components / renderers used by the view layer.
 */
class DrawableComponentRepository : public ComponentRepository<DrawableComponent> {
public:
    /**
     * @brief Creates a repository for all drawable components in the current stage.
     * @param entity_repo Repository with the entities to create drawable components for.
     */
    DrawableComponentRepository(EntityRepository &entity_repo, AssetsManager &assets_manager)
        : ComponentRepository<DrawableComponent>(entity_repo, std::make_unique<DrawableComponentFactory>(assets_manager)) {}

    /**
     * @brief Draws every drawable entity onto the layer stack.
     * @param layer Layer stack where the entities should be drawn.
     */
    void draw_all(LayerStack &layer);

    /**
     * @brief Update all renderers.
     * @param dt Time elapsed since the last update.
     * @param stage The current stage of the game.
     */
    void update_all(float dt, Stage &stage);
};

#endif
