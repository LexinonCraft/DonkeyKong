#ifndef PLATFORM_PAINTER_H
#define PLATFORM_PAINTER_H

#include "../view/Layer.hpp"
#include "../model/visitor/PlatformVisitor.hpp"

class PlatformPainter : public PlatformVisitor {
public:
    PlatformPainter(Layer &layer) : layer(layer) {}

    void visit(const Girder &girder) override;

private:
    Layer &layer;
};

#endif