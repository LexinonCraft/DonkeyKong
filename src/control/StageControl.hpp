#ifndef STAGE_CONTROL_HPP
#define STAGE_CONTROL_HPP

#include <cstdlib>
#include <memory>

#include "AbstractSceneControl.hpp"
#include "../model/Stage.hpp"
#include "../view/StageView.hpp"
#include "../model/DemoStage.hpp"

class StageControl : public AbstractSceneControl {
public:
    StageControl(sf::RenderWindow &window)
        : AbstractSceneControl(window), stage(std::unique_ptr<Stage>(new DemoStage(std::rand))), stage_view(window, *stage.get()) {
        window.setView(view);
        stage_view.set_view(view);
    } // TODO: allow stage selection

    virtual ~StageControl() {}

    bool handle_input() override;

    void update(float dt) override;

    void draw() override;

private:
    std::unique_ptr<Stage> stage;
    StageView stage_view;
};

#endif
