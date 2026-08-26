#include "DK/model/stages/Stage25M.hpp"

#include <SFML/System/Vector2.hpp>

#include "DK/model/entities/Player.hpp"

Stage25M::Stage25M(Id id_generator(), PlayerData &player_data) : Stage(id_generator, player_data) {
    auto p0 = entities.add_girder({-100, -20}, {constants::VIEW_WIDTH / 2.f, -20});
    auto p1 = entities.add_girder({constants::VIEW_WIDTH / 2.f, -20}, {constants::VIEW_WIDTH + 100, -40});
    auto p2 = entities.add_girder({0, -140}, {constants::VIEW_WIDTH - 50, -100});
    auto p3 = entities.add_girder({50, -200}, {constants::VIEW_WIDTH, -240});
    auto p4 = entities.add_girder({0, -350}, {constants::VIEW_WIDTH - 50, -310});
    auto p5 = entities.add_girder({50, -410}, {constants::VIEW_WIDTH, -450});
    auto p6 = entities.add_girder({380, -520}, {constants::VIEW_WIDTH - 50, -510});
    auto p7 = entities.add_girder({0, -520}, {380, -520});
    auto p8 = entities.add_girder({230, -610}, {360, -610});

    barrel_exit_y = p0->surface_y_at(0.f);

    entities.add_ladder(p0, p2, 220, true);
    entities.add_ladder(p1, p2, 500, false);
    entities.add_ladder(p2, p3, 260, false);
    entities.add_ladder(p2, p3, 90, false);
    entities.add_ladder(p3, p4, 180, true);
    entities.add_ladder(p3, p4, 300, false);
    entities.add_ladder(p3, p4, 500, false);
    entities.add_ladder(p4, p5, 450, true);
    entities.add_ladder(p4, p5, 200, false);
    entities.add_ladder(p4, p5, 100, false);
    entities.add_ladder(p5, p7, 240, false);
    entities.add_ladder(p5, p6, 490, false);
    entities.add_ladder(p7, p8, 340, false);

    entities.add_hammer_power_up({500.f, p2->surface_y_at(500.f) - constants::HAMMER_Y_OFFSET});
    entities.add_hammer_power_up({100.f, p5->surface_y_at(100.f) - constants::HAMMER_Y_OFFSET});

    final_girder = p8;

    donkey_kong = entities.add_donkey_kong(p7, 100, true);
    entities.add_barrel_stack(p7, 30);
    pauline = entities.add_pauline(p8, 275);

    entities.add_ladder(p7->surface_y_at(195.f), -750, 190, false, Ladder::Color::Cyan, false);
    entities.add_ladder(p7->surface_y_at(220.f), -750, 220, false, Ladder::Color::Cyan, false);

    player->enter_platform(p0, 50);
}

void Stage25M::update_while_running(float dt) {
    if (player->get_current_platform() == final_girder) {
        on_completed();
    }

    Stage::update_while_running(dt);
}

bool Stage25M::is_barrel_boundary_gap(const sf::Vector2f &position) const {
    const auto left_boundary = get_left_boundary();
    return left_boundary && position.x < *left_boundary && position.y >= barrel_exit_y;
}
