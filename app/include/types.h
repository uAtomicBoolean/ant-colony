#ifndef ANT_COLONY_TYPES_H
#define ANT_COLONY_TYPES_H

namespace sim::types {
    typedef struct Position {
        int x;
        int y;

        bool operator==(const Position &o_pos) const {
            return x == o_pos.x && y == o_pos.y;
        }
    } position_t;
}

#endif //ANT_COLONY_TYPES_H
