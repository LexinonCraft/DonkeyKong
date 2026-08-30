#include "DK/view/DrawableComponentRepository.hpp"

#include "DK/view/DrawableComponentFactory.hpp"

DrawableComponentRepository::DrawableComponentRepository(EntityRepository &entity_repo, AssetsManager &assets_manager)
    : ComponentRepository<DrawableComponent>(entity_repo, std::make_unique<DrawableComponentFactory>(assets_manager)) {}

void DrawableComponentRepository::draw_all(LayerStack &layer) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->draw(layer);
    }
}

void DrawableComponentRepository::update_all(float dt, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->update(dt, stage);
    }
}
