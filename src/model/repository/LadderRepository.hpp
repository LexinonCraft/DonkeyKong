#ifndef LADDER_REPOSITORY_H
#define LADDER_REPOSITORY_H

#include "../Ladder.hpp"
#include "../../util/Repository.hpp"

#include "../../util/Declarations.hpp"
class LadderRepository : public Repository<Ladder> {
public:
    LadderRepository(RepositoryElementId id_generator()) : Repository<Ladder>(id_generator) {}

    Ref<Ladder> add_ladder(Ref<Platform> lower_end, Ref<Platform> upper_end, float x_pos) {
        Ref<Ladder> ref = gen_ref();
        add(ref, std::make_shared<Ladder>(ref, lower_end, upper_end, x_pos));
        return ref;
    }
};

#endif