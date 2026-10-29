#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Unit080A53E4;

typedef struct {
    Unit080A53E4 *unit;
    u8 unknown_04[0x7C];
    void *entries;
} Object080A53E4;

typedef struct {
    Unit080A53E4 *unit;
} UnitEntry080A53E4;

typedef struct {
    Object080A53E4 *object;
    u8 unknown_04[0x0C];
    u32 flags;
    u8 unknown_14[0x18];
} EffectEntry080A53E4;

typedef struct {
    u8 unknown_00[0x10];
    u16 resource;
    u8 unknown_12[0x0E];
    EffectEntry080A53E4 entries[14];
    void *tasks[14];
    u8 count;
    u8 current;
} EffectSequence080A53E4;

extern u8 func_080A8858(const void *entry, u8 selector);
extern UnitEntry080A53E4 *func_08099494(void *entries, Object080A53E4 *state);
extern void func_080CE1B0(void *object, u8 enabled);
extern u32 func_080995C0(Object080A53E4 *object);

/* Complete [0x080A53E4, 0x080A54E0): 252 bytes, 117 instructions. */
void func_080A53E4(EffectSequence080A53E4 *state)
{
    s32 index;
    UnitEntry080A53E4 *entry;

    for (index = 0; index < state->count; index++) {
        if (func_080A8858(&state->entries[index], 3)) {
            while ((entry = func_08099494(state->entries[index].object->entries,
                                         state->entries[index].object)) != 0)
                func_080CE1B0(entry->unit, 0);
        }
        if (state->entries[index].flags & 0x800) {
            while ((entry = func_08099494(state->entries[index].object->entries,
                                         state->entries[index].object)) != 0)
                func_080CE1B0(entry->unit, 0);
            state->entries[index].object->unit->flags &= ~1;
            state->entries[index].object->unit->flags |= 0x20;
            if (state->resource == 0xB0 || state->resource == 0x6A)
                state->entries[index].object->unit->flags |= 0x100;
            func_080995C0(state->entries[index].object);
        }
    }
}
