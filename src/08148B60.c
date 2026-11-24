// Target: 0x08148B60-0x08149130, 1488 complete bytes (jump table at 0x08148BB4).
// Runs up to `share` steps (all steps when share < 0) of a 16x16 path search
// over the cells of a PathState: category 0 scans every cell through the
// callback, 1 sends the (-1, -1) end marker, 2 seeds the queue with the start
// node, 3 expands the front node in each direction for one or two steps, 4 is
// done.  Returns 0 when the search is done, 1 when the step budget runs out.
#include "ffta.h"

// Five-byte queue entry, also kept per cell; the 5-byte stride (lsls #2; adds)
// needs packed, since the ARM structure size boundary would round it to 8.
typedef struct {
    u8 direction : 7;
    u8 valid : 1;
    u8 climb;
    u8 cost;
    u8 x : 7;
    u8 wide : 1;    // a two-cell move, as src/08148A0C.c reads it
    u8 y;
} __attribute__((packed)) PathNode;

typedef struct {
    u8 value : 7;
    u8 enabled : 1;
    u8 mode : 4;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 unknown_flag : 1;
    PathNode node;
} __attribute__((packed)) PathCell;

// head and tail at 0x988/0x989, queue at 0x700 (movs #0xe0; lsls #3).
typedef struct {
    PathCell grid[16 * 16];
    PathNode queue[128];
    u8 category : 7;
    u8 active : 1;
    s8 max_climb;
    s8 max_drop;
    u8 max_cost;
    s8 scan_x;
    s8 scan_y;
    u8 start_x;
    u8 start_y;
    u8 head;
    u8 tail;
} __attribute__((packed)) PathState;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_2;
    u8 unknown_3;
} DirectionVector;

typedef void (*PathCallback)(void *object, s16 x, s16 y, u32 arg);
typedef void (*BufferInitializer)(void *destination, u32 size);

extern const DirectionVector data_089A5D3C[];
extern u8 data_03006100[4];
extern BufferInitializer g_callbacks_0836D4B8[];
extern void *func_081443FC(void *destination, const void *source, u32 size);

// The helpers below are inline functions.  The ROM converts every argument to
// its parameter type before the body uses it (the eager (s8)ny, (s8)nx pair
// ahead of the bounds test, and the (s8)/(u8) conversions of all requeue
// arguments ahead of the head load), and the &state->head address that the
// inlined bodies form is kept in one stack slot (sp+0x40), which only happens
// when the access is inlined.  queue_push is the push that wraps the tail at
// 127 (0x0814906E-0x0814908A); written out in place, its statements give a
// different register allocation (newdir in r5 rather than r4) and a
// 1482-byte function.  Case 2's push is written out: it increments the tail
// with no wrap at 127 (0x08148C28-0x08148C2C).  get_cell is the helper of
// src/08149194.c, src/08149384.c and src/081493AC.c, which take the same
// cells; the ROM converts a neighbour's coordinates to its s16 parameters
// (lsls/asrs #16 at 0x08148E40-0x08148E46).
static inline PathCell *get_cell(PathCell *grid, s16 x, s16 y)
{
    return &grid[y * 16 + x];
}

static inline s32 in_bounds(s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15)
        return 0;
    return 1;
}

static inline PathNode *queue_front(PathState *state)
{
    return &state->queue[state->head];
}

static inline PathNode *queue_push(PathState *state)
{
    PathNode *node;
    s32 tail;

    node = &state->queue[state->tail];
    tail = state->tail + 1;
    if (tail > 127)
        tail = 0;
    state->tail = tail;
    return node;
}

static inline void advance_head(PathState *state)
{
    s32 head;

    head = state->head + 1;
    if (head > 127)
        head = 0;
    state->head = head;
}

// Updates a queued entry for (x, y) when the new route is better; returns 1
// when an entry for (x, y) is already queued.
static inline s32 requeue(PathState *state, s8 x, s8 y, u8 climb,
                          s8 direction, u8 cost, u8 wide)
{
    s32 index;
    PathNode *node;
    s32 next;

    index = state->head;
    node = &state->queue[index];
    while (node->valid) {
        if (node->x == x && node->y == y) {
            if (node->cost < cost)
                return 1;
            if (node->cost == cost) {
                if (node->climb < climb)
                    return 1;
                if (node->climb == climb) {
                    if (wide == node->wide || wide != 0)
                        return 1;
                }
            }
            node->climb = climb;
            node->cost = cost;
            node->direction = direction;
            node->wide = wide;
            return 1;
        }
        next = index + 1;
        if (next > 127)
            next = 0;
        index = next;
        /* BUG: the scan ends only at an empty slot (0x08148FD2-0x08148FE0,
           0x0814904C-0x0814906C).  The queue holds 128 entries and the node
           being expanded stays in it until its expansion ends, so with 127
           cells pending every slot is taken, and a route to a cell that is
           not queued makes this loop run forever.  Nothing limits the cells
           pending to fewer than 128: docs/bugs/08148B60/ has a 16x16 grid
           that freezes the search. */
#ifdef BUGFIX
        if (index == state->tail)
            break;
#endif
        node = &state->queue[index];
    }
    return 0;
}

u32 func_08148B60(void *object, PathCallback callback, s8 share, u32 arg)
{
    s32 i;
    PathState *state = object;

    i = 0;
    for (;;) {
        if (share >= 0 && i >= share)
            return 1;
        switch (state->category) {
        case 2: {
            PathNode *node;

            /* Case 0 passes scan_x as x and scan_y as y; these two stores
               put the start in the other way round.  Neither is read again
               before the next scan, and the functions that set category 0
               (func_0814914C, func_08149268, func_081492A8) clear both. */
            state->scan_y = state->start_x;
            state->scan_x = state->start_y;
            node = &state->queue[state->tail];
            node->direction = 15;
            node->climb = 0;
            node->cost = 0;
            node->valid = 1;
            node->wide = 0;
            node->x = state->start_x;
            node->y = state->start_y;
            state->tail++;
            state->category = 3;
            continue;
        }
        case 0: {
            s32 n;

            for (n = 0; n < 8; n++) {
                callback(object, state->scan_x, state->scan_y, arg);
                state->scan_x++;
                if (state->scan_x > 15) {
                    state->scan_x = 0;
                    state->scan_y++;
                    if (state->scan_y > 15) {
                        state->head = 0;
                        state->tail = 0;
                        g_callbacks_0836D4B8[0](state->queue,
                                                sizeof(state->queue));
                        state->category = 1;
                    }
                }
            }
            break;
        }
        case 1:
            callback(object, -1, -1, arg);
            state->category = 2;
            continue;
        case 3: {
            s32 ndirs;
            PathNode *node;
            s32 dir;
            PathCell *cell;
            u8 steps;
            u8 prev_cost;

            prev_cost = 0;
            ndirs = 4;
            node = queue_front(state);
            if (node->valid) {
                s32 k;

                dir = node->direction;
                if (dir == 15) {
                    for (k = 0; k < 4; k++)
                        data_03006100[k] = k + 1;
                } else {
                    dir++;
                    ndirs = 3;
                    data_03006100[0] = dir;
                    data_03006100[1] = dir - 1;
                    data_03006100[2] = dir + 1;
                }
                cell = get_cell(state->grid, node->x, node->y);
                func_081443FC(&cell->node, node, sizeof(PathNode));
                steps = 2;
                if (cell->flag5)
                    steps = 1;
                advance_head(state);

                for (k = 0; k < ndirs; k++) {
                    u8 j;
                    s8 prev_diff;
                    u8 cost;
                    s8 diff;

                    dir = data_03006100[k];
                    prev_diff = 0;
                    for (j = 0; j < steps;
                         j++, prev_diff = diff, prev_cost = cost) {
                        s32 nx;
                        s32 ny;
                        PathCell *next;
                        s32 climb;
                        s8 newdir;
                        PathNode *queued;

                        nx = node->x + (data_089A5D3C[dir].x << j);
                        ny = node->y + (data_089A5D3C[dir].y << j);
                        if (!in_bounds(nx, ny))
                            break;
                        next = get_cell(state->grid, nx, ny);
                        if (!next->enabled)
                            break;
                        cost = j + (next->mode + node->cost);
                        diff = next->value - cell->value;
                        if (j != 0) {
                            s32 last = next->mode + prev_cost;

                            if (last < cost)
                                break;
                            if (last == cost) {
                                if ((prev_diff < 0 ? -prev_diff : prev_diff)
                                    <= (diff < 0 ? -diff : diff))
                                    break;
                            }
                        }
                        if (state->max_cost != 0xFF && cost > state->max_cost)
                            continue;
                        if (next->flag4) {
                            cost = 0xFF;
                            continue;
                        }
                        if (j != 0 && (diff > 0 || prev_diff > 0))
                            continue;
                        if (diff < state->max_drop || diff > state->max_climb)
                            continue;
                        newdir = dir - 1;
                        if (newdir < 0)
                            newdir += 4;
                        if (newdir > 3)
                            newdir -= 4;
                        climb = (diff < 0 ? -diff : diff) + node->climb;
                        if (climb > 255)
                            climb = 255;
                        if (next->node.valid) {
                            if (next->node.cost < cost)
                                continue;
                            if (next->node.cost == cost) {
                                if (next->node.climb < climb)
                                    continue;
                                if (next->node.climb == climb) {
                                    if (j == next->node.wide || j != 0)
                                        continue;
                                }
                            }
                        }
                        if (!requeue(state, nx, ny, climb, newdir, cost, j)) {
#ifdef BUGFIX
                            /* A full queue: the slot at the tail is the node
                               being expanded.  Drop the route rather than
                               overwrite it; the cell can still be reached
                               later, once slots are free again. */
                            if (state->queue[state->tail].valid)
                                continue;
#endif
                            queued = queue_push(state);
                            queued->valid = 1;
                            queued->cost = cost;
                            queued->x = nx;
                            queued->y = ny;
                            queued->direction = newdir;
                            queued->wide = j;
                            queued->climb = climb;
                        }
                    }
                }
                node->valid = 0;
            } else {
                state->category = 4;
            }
            break;
        }
        case 4:
            return 0;
        }
        i++;
    }
}
