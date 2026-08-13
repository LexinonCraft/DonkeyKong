#ifndef SCENE_HPP
#define SCENE_HPP

#include "Declarations.hpp"

class Scene {
public:
    virtual ~Scene() {}

    virtual void update(float dt) = 0;

    virtual void accept(SceneVisitor &visitor) = 0;
};

#endif
