#ifndef LADDER_REPOSITORY_H
#define LADDER_REPOSITORY_H

#include <memory>

#include "../Ladder.hpp"
#include "../../util/Repository.hpp"
#include "../../util/Declarations.hpp"

class LadderRepository : public Repository<Ladder> {
public:
    LadderRepository(RepositoryElementId id_generator()) : Repository<Ladder>(id_generator) {}

    std::shared_ptr<Ladder> add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos) {
        Ref<Ladder> ref = gen_ref();
        return add(ref, std::make_shared<Ladder>(ref, lower_end, upper_end, x_pos));
    }
};

#endif