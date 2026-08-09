#include "SFML/System/Vector2.hpp"

#include "DemoLevel.hpp"

DemoLevel::DemoLevel(RepositoryElementId id_generator()) : Level(id_generator) {
    auto p1 = platforms.add_girder({120, -500}, {500, -460});
    auto p2 = platforms.add_girder({80, -360}, {540, -400});
    auto p3 = platforms.add_girder({40, -300}, {520, -260});
    auto p4 = platforms.add_girder({80, -160}, {560, -200});

    ladders.add_ladder(p2, p1, 200.0f);
    ladders.add_ladder(p3, p2, 300.0f);
    ladders.add_ladder(p4, p3, 500.0f);

    entities.add_barrel({300, -500});
}
