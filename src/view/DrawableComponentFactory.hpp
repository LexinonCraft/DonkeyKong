#ifndef DRAWABLE_COMPONENT_FACTORY_HPP
#define DRAWABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/view/Declarations.hpp"
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

/**
 * @brief Factory for creating drawable components / renderers for entities.
 */
class DrawableComponentFactory : public AbstractComponentFactory<DrawableComponent>, private EntityVisitor {
public:
    /**
     * @brief Initializes the factory.
     *
     * @param assets_manager The assets manager to be passed to the renderers.
     */
    DrawableComponentFactory(AssetsManager &assets_manager) : assets_manager(assets_manager) {}

    /**
     * @brief Creates the drawable component / renderer for an entity using visitor dispatch.
     * @param entity Entity to create a drawable component for.
     * @return Unique pointer to the drawable component.
     */
    std::unique_ptr<DrawableComponent> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        entity->accept(*this);
        return std::move(component);
    }

private:
    std::unique_ptr<DrawableComponent> component;
    AssetsManager &assets_manager;

    void visit(Barrel &barrel) override {
        component = std::make_unique<BarrelRenderer>(std::static_pointer_cast<Barrel>(barrel.shared_from_this()), assets_manager);
    }

    void visit(Girder &girder) override {
        component = std::make_unique<GirderRenderer>(std::static_pointer_cast<Girder>(girder.shared_from_this()), assets_manager);
    }

    void visit(Player &player) override {
        component = std::make_unique<PlayerRenderer>(std::static_pointer_cast<Player>(player.shared_from_this()), assets_manager);
    }

    void visit(Ladder &ladder) override {
        component = std::make_unique<LadderRenderer>(std::static_pointer_cast<Ladder>(ladder.shared_from_this()), assets_manager);
    }

    void visit(HammerPowerUp &hammer) override {
        component = std::make_unique<HammerRenderer>(std::static_pointer_cast<HammerPowerUp>(hammer.shared_from_this()), assets_manager);
    }

    void visit(DonkeyKong &donkey_kong) override {
        component =
            std::make_unique<DonkeyKongRenderer>(std::static_pointer_cast<DonkeyKong>(donkey_kong.shared_from_this()), assets_manager);
    }

    void visit(BarrelStack &barrel_stack) override {
        component =
            std::make_unique<BarrelStackRenderer>(std::static_pointer_cast<BarrelStack>(barrel_stack.shared_from_this()), assets_manager);
    }

    void visit(Pauline &pauline) override {
        component = std::make_unique<PaulineRenderer>(std::static_pointer_cast<Pauline>(pauline.shared_from_this()), assets_manager);
    }

    void visit(DissolvingPlatform &dissolving_platform) override {
        component = std::make_unique<DissolvingPlatformRenderer>(
            std::static_pointer_cast<DissolvingPlatform>(dissolving_platform.shared_from_this()));
    }

    void visit(Ghost &ghost) override {
        component = std::make_unique<GhostRenderer>(std::static_pointer_cast<Ghost>(ghost.shared_from_this()), assets_manager);
    }

    void visit(Beam &beam) override { component = std::make_unique<BeamRenderer>(std::static_pointer_cast<Beam>(beam.shared_from_this())); }
};

#endif
