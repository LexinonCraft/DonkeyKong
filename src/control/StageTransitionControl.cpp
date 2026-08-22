#include "DK/control/StageTransitionControl.hpp"

void StageTransitionControl::handle_event(sf::Event *event) {
    // No event handling for the title screen
}

void StageTransitionControl::handle_input() {
    // No continuous input handling for the title screen
}

void StageTransitionControl::update(float dt) {
    time_elapsed += dt;
}

void StageTransitionControl::draw() {
    stage_transition_view.draw();
}

AbstractSceneControl::NextScene StageTransitionControl::get_next_scene() const {
    return time_elapsed >= 5.f ? NextScene::Stage : NextScene::Stay;
}
