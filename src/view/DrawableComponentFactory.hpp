#ifndef DRAWABLE_COMPONENT_FACTORY_HPP
#define DRAWABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/EntityVisitor.hpp"
#include "DK/view/Declarations.hpp"

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
    DrawableComponentFactory(AssetsManager &assets_manager);

    ~DrawableComponentFactory() override;

    std::unique_ptr<DrawableComponent> create_component_for(std::shared_ptr<BaseEntity> entity) override;

private:
    std::unique_ptr<DrawableComponent> component;
    AssetsManager &assets_manager;

    void visit(Barrel &barrel) override;
    void visit(Girder &girder) override;
    void visit(Player &player) override;
    void visit(Ladder &ladder) override;
    void visit(HammerPowerUp &hammer) override;
    void visit(DonkeyKong &donkey_kong) override;
    void visit(BarrelStack &barrel_stack) override;
    void visit(Pauline &pauline) override;
    void visit(DissolvingPlatform &dissolving_platform) override;
    void visit(Ghost &ghost) override;
    void visit(Beam &beam) override;
};

#endif
