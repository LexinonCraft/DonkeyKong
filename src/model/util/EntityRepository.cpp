#include "DK/model/util/EntityRepository.hpp"

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

std::shared_ptr<Barrel> EntityRepository::add_barrel(sf::Vector2f position) {
    return add_entity(std::make_shared<Barrel>(gen_ref(), position));
}

std::shared_ptr<HammerPowerUp> EntityRepository::add_hammer_power_up(sf::Vector2f position) {
    return add_entity(std::make_shared<HammerPowerUp>(gen_ref(), position));
}

std::shared_ptr<Girder> EntityRepository::add_girder(sf::Vector2f left, sf::Vector2f right) {
    return add_entity(std::make_shared<Girder>(gen_ref(), left, right));
}

std::shared_ptr<Girder> EntityRepository::add_girder(sf::Vector2f left, sf::Vector2f right, Girder::Color color) {
    return add_entity(std::make_shared<Girder>(gen_ref(), left, right, color));
}

std::shared_ptr<Player> EntityRepository::add_player() { return add_entity(std::make_shared<Player>(gen_ref())); }

std::shared_ptr<Ladder> EntityRepository::add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end,
                                                     float x_position, bool broken) {
    return add_entity(std::make_shared<Ladder>(gen_ref(), lower_end, upper_end, x_position, broken));
}

std::shared_ptr<Ladder> EntityRepository::add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end,
                                                     float x_position, bool broken, Ladder::Color color) {
    return add_entity(std::make_shared<Ladder>(gen_ref(), lower_end, upper_end, x_position, broken, color));
}

std::shared_ptr<Ladder> EntityRepository::add_ladder(float lower_y, float upper_y, float x_pos, bool broken, Ladder::Color color,
                                                     bool active_for_player) {
    return add_entity(std::make_shared<Ladder>(gen_ref(), lower_y, upper_y, x_pos, broken, color, active_for_player));
}

std::shared_ptr<DonkeyKong> EntityRepository::add_donkey_kong(std::shared_ptr<Platform> platform, float x_position, bool throw_barrels) {
    return add_entity(std::make_shared<DonkeyKong>(gen_ref(), platform, x_position, throw_barrels));
}

std::shared_ptr<BarrelStack> EntityRepository::add_barrel_stack(std::shared_ptr<Platform> platform, float x_position) {
    return add_entity(std::make_shared<BarrelStack>(gen_ref(), platform, x_position));
}

std::shared_ptr<Pauline> EntityRepository::add_pauline(std::shared_ptr<Platform> platform, float x_position) {
    return add_entity(std::make_shared<Pauline>(gen_ref(), platform, x_position));
}

std::shared_ptr<DissolvingPlatform> EntityRepository::add_dissolving_platform(sf::Vector2f position, float width) {
    return add_entity(std::make_shared<DissolvingPlatform>(gen_ref(), position, width));
}

std::shared_ptr<Ghost> EntityRepository::add_ghost(std::shared_ptr<Platform> platform, float x_pos) {
    return add_entity(std::make_shared<Ghost>(gen_ref(), platform, x_pos));
}

std::shared_ptr<Beam> EntityRepository::add_beam(std::shared_ptr<Platform> lower_platform, std::shared_ptr<Platform> upper_platform,
                                                 float x_pos) {
    return add_entity(std::make_shared<Beam>(gen_ref(), lower_platform, upper_platform, x_pos));
}

void EntityRepository::handle_additions() {
    while (!pending_additions.empty()) {
        std::shared_ptr<BaseEntity> entity = pending_additions.front();
        pending_additions.pop();

        entities[entity->get_id()] = entity;

        for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
            it->second->on_entity_added(entity);
        }
    }
}

void EntityRepository::handle_deletions() {
    while (!pending_deletions.empty()) {
        Id id = pending_deletions.front();
        pending_deletions.pop();

        auto it = entities.find(id);
        if (it != entities.end()) {
            for (auto obs_it = observer_registry.begin(); obs_it != observer_registry.end(); ++obs_it) {
                obs_it->second->on_entity_removed(it->second);
            }
            entities.erase(it);
        }
    }

    for (auto it = entities.begin(); it != entities.end(); ++it) {
        it->second->check_referenced_entities();
    }
}

void EntityRepository::clear_secondary_entities() {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (it->second->is_secondary_entity()) {
            it->second->destroy();
        }
    }

    // Remove all secondary entities from the pending additions queue by rebuilding it without the secondary entities
    std::queue<std::shared_ptr<BaseEntity>> temp_queue;
    while (!pending_additions.empty()) {
        auto entity = pending_additions.front();
        pending_additions.pop();
        if (!entity->is_secondary_entity()) {
            temp_queue.push(entity);
        }
    }
    pending_additions = std::move(temp_queue);
}

Ref EntityRepository::gen_ref() { return Ref(id_generator(), *this); }
