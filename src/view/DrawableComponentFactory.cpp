#include "DK/view/DrawableComponentFactory.hpp"

#include <utility>

#include "DK/model/entities/Barrel.hpp"
#include "DK/model/entities/BarrelStack.hpp"
#include "DK/model/entities/Beam.hpp"
#include "DK/model/entities/DissolvingPlatform.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/model/entities/Ghost.hpp"
#include "DK/model/entities/Girder.hpp"
#include "DK/model/entities/HammerPowerUp.hpp"
#include "DK/model/entities/Ladder.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/view/DrawableComponent.hpp"
#include "DK/view/renderers/BarrelRenderer.hpp"
#include "DK/view/renderers/BarrelStackRenderer.hpp"
#include "DK/view/renderers/BeamRenderer.hpp"
#include "DK/view/renderers/DissolvingPlatformRenderer.hpp"
#include "DK/view/renderers/DonkeyKongRenderer.hpp"
#include "DK/view/renderers/GhostRenderer.hpp"
#include "DK/view/renderers/GirderRenderer.hpp"
#include "DK/view/renderers/HammerRenderer.hpp"
#include "DK/view/renderers/LadderRenderer.hpp"
#include "DK/view/renderers/PaulineRenderer.hpp"
#include "DK/view/renderers/PlayerRenderer.hpp"

DrawableComponentFactory::DrawableComponentFactory(AssetsManager &assets_manager) : assets_manager(assets_manager) {}

DrawableComponentFactory::~DrawableComponentFactory() = default;

std::unique_ptr<DrawableComponent> DrawableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    entity->accept(*this);
    return std::move(component);
}

void DrawableComponentFactory::visit(Barrel &barrel) {
    component = std::make_unique<BarrelRenderer>(std::static_pointer_cast<Barrel>(barrel.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(Girder &girder) {
    component = std::make_unique<GirderRenderer>(std::static_pointer_cast<Girder>(girder.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(Player &player) {
    component = std::make_unique<PlayerRenderer>(std::static_pointer_cast<Player>(player.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(Ladder &ladder) {
    component = std::make_unique<LadderRenderer>(std::static_pointer_cast<Ladder>(ladder.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(HammerPowerUp &hammer) {
    component = std::make_unique<HammerRenderer>(std::static_pointer_cast<HammerPowerUp>(hammer.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(DonkeyKong &donkey_kong) {
    component = std::make_unique<DonkeyKongRenderer>(std::static_pointer_cast<DonkeyKong>(donkey_kong.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(BarrelStack &barrel_stack) {
    component =
        std::make_unique<BarrelStackRenderer>(std::static_pointer_cast<BarrelStack>(barrel_stack.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(Pauline &pauline) {
    component = std::make_unique<PaulineRenderer>(std::static_pointer_cast<Pauline>(pauline.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(DissolvingPlatform &dissolving_platform) {
    component =
        std::make_unique<DissolvingPlatformRenderer>(std::static_pointer_cast<DissolvingPlatform>(dissolving_platform.shared_from_this()));
}

void DrawableComponentFactory::visit(Ghost &ghost) {
    component = std::make_unique<GhostRenderer>(std::static_pointer_cast<Ghost>(ghost.shared_from_this()), assets_manager);
}

void DrawableComponentFactory::visit(Beam &beam) {
    component = std::make_unique<BeamRenderer>(std::static_pointer_cast<Beam>(beam.shared_from_this()));
}
