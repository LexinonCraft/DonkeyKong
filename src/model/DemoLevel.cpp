#include <cstdlib>
#include "SFML/System/Vector2.hpp"

#include "DemoLevel.hpp"
#include "Girder.hpp"
#include "Ladder.hpp"
#include "Barrel.hpp"

DemoLevel::DemoLevel() {
    Girder *g1 = new Girder({120, -500}, {500, -460});
    Girder *g2 = new Girder({80, -360}, {540, -400});
    Girder *g3 = new Girder({40, -300}, {520, -260});
    Girder *g4 = new Girder({80, -160}, {560, -200});
    add_platform(std::rand, g1);
    add_platform(std::rand, g2);
    add_platform(std::rand, g3);
    add_platform(std::rand, g4);

    Ladder *l1 = new Ladder(g2, g1, 200.0f);
    Ladder *l2 = new Ladder(g3, g2, 300.0f);
    Ladder *l3 = new Ladder(g4, g3, 500.0f);
    add_ladder(std::rand, l1);
    add_ladder(std::rand, l2);
    add_ladder(std::rand, l3);

    add_entity(std::rand, new Barrel({300, -500}));
}
