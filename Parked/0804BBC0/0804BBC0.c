#include "ffta.h"

typedef struct {
    u8 route;
    u8 node;
    u8 unknown_02[2];
} __attribute__((packed)) MapEdge;

typedef struct {
    u8 x, y;
    MapEdge edges[4];
    u8 unknown_12[2];
} MapNode;

typedef struct {
    u8 count;
    u8 unknown_01[3];
    const s8 *coordinates;
} CoordinateSequence;

extern const MapNode data_08391E40[];
extern const CoordinateSequence data_083931B0[];
extern u8 data_02002E58;

void func_0804BBC0(u8 start, u8 *distance, u8 *previous)
{
    u8 neighbors[4];
    u8 routes[4];
    u16 cost[32];
    s16 current, last;
    u16 i;

    for (i = 0; i < 32; i++) {
        distance[i] = previous[i] = 0xff;
        cost[i] = 0xefff;
    }
    current = start;
    last = current;
    distance[current] = 0;
    cost[current] = 0;
    /* Stop after a full scan without updating a predecessor. */
    do {
        if (distance[current] != 0xff) {
            const MapNode *node = &data_08391E40[current];

            neighbors[0] = node->edges[0].node;
            neighbors[1] = node->edges[1].node;
            neighbors[2] = node->edges[2].node;
            neighbors[3] = node->edges[3].node;
            routes[0] = node->edges[0].route;
            routes[1] = node->edges[1].route;
            routes[2] = node->edges[2].route;
            routes[3] = node->edges[3].route;
            for (i = 0; i < 4; i++) {
                if (!(data_02002E58 & 1) && neighbors[i] == 8)
                    continue;
                if (!(data_02002E58 & 2) && neighbors[i] == 27)
                    continue;
                if (routes[i] == 0)
                    continue;
                if (distance[current] + 1 > distance[neighbors[i]])
                    continue;
                /* The tie-break cost is written only for equal-hop routes. */
                if (distance[current] + 1 == distance[neighbors[i]]) {
                    s32 next_cost = cost[current] + data_083931B0[routes[i] - 1].count;

                    if (next_cost >= cost[neighbors[i]])
                        continue;
                    cost[neighbors[i]] = next_cost;
                }
                distance[neighbors[i]] = distance[current] + 1;
                previous[neighbors[i]] = current;
                last = current;
            }
        }
        current++;
        if (current > 31)
            current = 0;
    } while (last != current);
}
