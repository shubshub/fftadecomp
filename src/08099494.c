#include "ffta.h"

// Complete target [0x08099494,0x0809951E): 138 bytes, 69 instructions.
typedef struct {
    void *object;
    u8 unknown_04[0x58];
    s16 unknown_5C;
} Entry08099494;

typedef struct {
    u8 unknown_000[0x104];
    u8 unknown_104;
} Unit08099494;

typedef struct {
    Unit08099494 *unit;
} State08099494;

extern u32 func_08099CDC(void *owner, Entry08099494 **out);
extern u8 func_080CDBCC(const void *object);
extern u8 func_080CE410(const void *object);
extern u8 func_0812E4A8(const void *object);

Entry08099494 *func_08099494(void *owner, State08099494 *state)
{
    Entry08099494 *entries[13];
    s32 count;
    s32 i;
    Entry08099494 *best;
    s32 best_rank;

    count = func_08099CDC(owner, entries);
    best = 0;
    best_rank = 0x400;
    for (i = 0; i < count; i++) {
        if (entries[i]->unknown_5C < best_rank && func_080CDBCC(entries[i]->object) &&
            state->unit->unknown_104 == func_080CE410(entries[i]->object) &&
            func_0812E4A8(entries[i]->object)) {
            best_rank = entries[i]->unknown_5C;
            best = entries[i];
        }
    }
    return best;
}
