#ifndef ENTITY_PAINTER_H
#define ENTITY_PAINTER_H

#include "../view/Layer.hpp"
#include "../model/visitor/EntityVisitor.hpp"

class EntityPainter : public EntityVisitor {
public:
    EntityPainter(Layer &layer) : layer(layer) {}

    void visit(const Barrel &barrel) override;
    void visit(const Player &player) override;

private:
    Layer &layer;
};

#endif
