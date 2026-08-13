#ifndef SCENE_VISITOR_HPP
#define SCENE_VISITOR_HPP

#include "Declarations.hpp"

class SceneVisitor {
public:
    virtual ~SceneVisitor() {}

    virtual void visit(Stage &scene) = 0;

    virtual void visit(TitleScreenScene &scene) = 0;
};

#endif
