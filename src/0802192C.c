#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x0e];
    u16 tile;
    u16 saved_tile;
    u16 increment;
} Entry0802192C;

typedef struct {
    u16 tile;
    u8 unknown_02[2];
    Entry0802192C **entries;
    Entry0802192C **cursor;
    int processed;
    int count;
    u8 flags;
} State0802192C;

/* Complete [0x0802192C, 0x08021A3C): 272 bytes, 131 instructions.
 * f0b54f464646c0b48846041c626800208446206984450ada031c1168488a898a88426cd1
 * 01218c4404329c45f5dbe1682069814201db002062e000208446c4455dda01218946207d
 * 49460140071ca668258800293ad13368588a2a1c011c8a4210d1e1680131e16020698142
 * e3dad88a5b8ac01820803068418a8182a0680430a060e0e7914221d2281a0004030c2069
 * 8000043861680a18b2420ed080260a4d1168488ac018888211680868304328400860043a
 * a0688242f2d1217d484608432075c44617e00000fffffcfffe203840207530688582a368
 * 04cb1068802108430a4908401060e0680130e060d08a218840182080a36001208444c445
 * a3db012018bc9846a146f0bc02bc0847fffffcff
 */
u32 func_0802192C(void *object, int steps)
{
    State0802192C *state = object;
    Entry0802192C **scan = state->entries;
    int i;

    for (i = 0; i < state->count; i++, scan++) {
        if ((*scan)->tile != (*scan)->saved_tile)
            return 1;
    }
    if (state->processed >= state->count)
        return 0;

    for (i = 0; i < steps; i++) {
        for (;;) {
            if (!(state->flags & 1) && state->tile == (*state->cursor)->tile) {
                state->processed++;
                if (state->processed >= state->count)
                    return 0;
                state->tile = (*state->cursor)->tile + (*state->cursor)->increment;
                (*state->cursor)->saved_tile = (*state->cursor)->tile;
                state->cursor++;
                continue;
            }
            if (!(state->flags & 1) && (*state->cursor)->tile < state->tile) {
                u32 offset = (u16)(state->tile - (*state->cursor)->tile);
                Entry0802192C **p = &state->entries[state->count - 1];

                for (; p != state->cursor; p--) {
                    (*p)->saved_tile = (*p)->tile + offset;
                    (*p)->flags = ((*p)->flags | 0x80) & ~0x30000;
                }
                state->flags |= 1;
                i = steps;
            } else {
                state->flags &= ~1;
                (*state->cursor)->saved_tile = state->tile;
                (*state->cursor)->flags = ((*state->cursor)->flags | 0x80) & ~0x30000;
                state->processed++;
                state->tile += (*state->cursor)->increment;
                state->cursor++;
            }
            break;
        }
    }
    return 1;
}
