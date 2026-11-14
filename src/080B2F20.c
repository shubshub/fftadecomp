#include "ffta.h"

// Complete [0x080B2F20, 0x080B3150): 560 bytes, 206 instructions,
// including the jump table at 0x080B3050 and the literal pools.

typedef void (*BufferInitializer)(void *destination, u32 size);
typedef u32 (*Handler080B2F20)(void *, void *, u32, const void *);

typedef struct {
    void *unit;
} Owner080B2F20;

typedef struct {
    Owner080B2F20 *owner;
    u8 unknown_004[0x32];
    u16 skills[3];
    u8 unknown_03C;
    u8 skill_count;
    s8 direction;
    u8 unknown_03F;
    u8 active;
    u8 unknown_041;
    u16 tile;
    u8 unknown_044[0x144];
    u8 listed;
    u8 unknown_189[3];
} Entry080B2F20;

typedef struct {
    u8 unknown_00[0x1F];
    s8 direction;
} Leader080B2F20;

typedef struct {
    Entry080B2F20 entries[13];
    Leader080B2F20 *leader;
    u8 unknown_1420[4];
    Owner080B2F20 *owners[13];
    Owner080B2F20 *listed[13];
    Handler080B2F20 handlers[13];
    u16 offsets[13];
    u8 unknown_14DA[0x5E];
    u8 count;
    u8 listed_count;
    u8 unknown_153A[8];
    u8 next_direction;
    u8 unknown_1543[0x19];
    u16 tile;
} State080B2F20;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080A9F24(void *, void *, u32, const void *);
extern u32 func_080AA29C(void *, void *, u32, const void *);
extern u32 func_080AA894(void *, void *, u32, const void *);
extern u32 func_080AADBC(void *, void *, u32, const void *);
extern u32 func_080AB358(void *, void *, u32, const void *);

static inline void InitEntry(Entry080B2F20 *entry, Owner080B2F20 *owner)
{
    g_callbacks_0836D4B8[0](entry, sizeof(*entry));
    entry->owner = owner;
    entry->active = 1;
    entry->unknown_03C = 0;

    entry->skill_count = func_0812F0D8(entry->owner->unit, entry->skills);
    if (entry->skill_count == 0) {
        entry->skill_count = 1;
        entry->skills[0] = 0;
    }
}

static inline u8 IsListed(Owner080B2F20 *owner, Owner080B2F20 **listed,
                          s32 count)
{
    s32 j;

    for (j = 0; j < count; j++, listed++) {
        if (*listed == owner)
            return 1;
    }
    return 0;
}

void func_080B2F20(State080B2F20 *state)
{
    s32 i;
    s32 direction = state->leader->direction + 2;

    for (i = 0; i < state->count; direction++, i++) {
        if (direction > 3)
            direction -= 4;

        InitEntry(&state->entries[i], state->owners[i]);
        state->entries[i].listed = IsListed(state->owners[i], state->listed,
                                              state->listed_count);
        state->offsets[i] = i * 34;
        state->entries[i].direction = direction;
        state->entries[i].tile = state->tile;

        switch (func_080CA7A4(state->entries[i].skills[0], 3)) {
        case 13:
        case 14:
            state->handlers[i] = func_080AADBC;
            break;
        case 19:
            state->handlers[i] = func_080AB358;
            break;
        case 15:
            state->handlers[i] = func_080AA29C;
            break;
        case 9:
            state->handlers[i] = func_080AA894;
            break;
        default:
            if (func_080CA7A4(state->entries[i].skills[0], 6) == 2)
                state->handlers[i] = func_080AA894;
            else
                state->handlers[i] = func_080A9F24;
            break;
        }
    }

    if (direction > 3)
        direction -= 4;
    state->next_direction = direction;
}
