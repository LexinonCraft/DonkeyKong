#ifndef TITLE_SCREEN_SCENE_HPP
#define TITLE_SCREEN_SCENE_HPP

#include "Scene.hpp"
#include "SceneVisitor.hpp"

class TitleScreenScene : public Scene {
public:
    virtual ~TitleScreenScene() {}

    void update(float dt) override {
        // No-op for the title screen scene.
    }

    void accept(SceneVisitor &visitor) override {
        visitor.visit(*this);
    }
};

#endif
