#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 type;
    u8 unknown_05[2];
    u8 category;
    u8 unknown_08[0x100];
} Unit080611F0;

typedef struct {
    u8 unknown_00[0x14];
    u8 selected;
} SelectionState080611F0;

typedef void (*BufferInitializer080611F0)(void *destination, u32 size);
extern BufferInitializer080611F0 const g_callbacks_0836D4B8[];
extern SelectionState080611F0 g_state_020020D0;
extern Unit080611F0 g_state_02000080[];
extern u32 func_080CE4DC(u16 identifier, u8 selector);
extern void func_08071DC8(u8 selected, u8 *indices);
extern u8 func_080C8194(const void *unit, u8 type);
extern u8 func_080C8310(const void *unit);
extern u8 func_080C82D8(const void *unit);
extern u8 func_080C82F4(const void *unit);
extern u8 func_080C93F0(u8 category);

/* Complete [0x080611F0, 0x080612C8): 216 bytes, 93 instructions. */
u8 func_080611F0(u16 identifier, Unit080611F0 **output, u8 *indices)
{
    u32 category;
    s32 count;
    s32 i;

    g_callbacks_0836D4B8[0](output, 0x5C);
    category = func_080CE4DC(identifier, 0x30);
    func_08071DC8(g_state_020020D0.selected, indices);
    count = 0;

    for (i = 0; i < 24; i++) {
        u8 *index = &indices[i];
        Unit080611F0 *unit;

        if (*index == 0xFF)
            continue;
        unit = &g_state_02000080[*index];
        if (unit->type == 0 || func_080C8194(unit, 2) ||
            func_080C8194(unit, 8) || func_080C8310(unit) ||
            func_080C82D8(unit) || func_080C82F4(unit))
            continue;
        if (identifier != 0 && category != 0 &&
            func_080C93F0(unit->category) != category)
            continue;
        output[count++] = unit;
    }
    return count;
}
