#include "ffta.h"

/* Target: complete [0x08132E2C, 0x08132EA0), 116 bytes. */
typedef struct {
    u8 unknown_00[6];
    u8 category;
    u8 unknown_07[0x39];
    u8 values[256];
} State08132E2C;

typedef struct {
    u32 unknown_00;
    u16 id;
} Item08132E2C;

extern u32 func_080CCD50(u16, u8);
extern u16 func_08132DDC(State08132E2C *, const Item08132E2C *);
extern const u8 *func_080CD480(u8, u8);

u16 func_08132E2C(State08132E2C *state, const Item08132E2C *const *items,
                    s32 count, s32 *selected_index)
{
    s32 index;
    u16 id;
    u8 value;

    for (index = 0; index < count; index++) {
        if (func_080CCD50(items[index]->id, 25) == 0)
            continue;
        id = func_08132DDC(state, items[index]);
        if (id == 0)
            continue;
        value = state->values[id] & 0x7f;
        if (value < func_080CD480(state->category, id)[7]) {
            *selected_index = index;
            return id;
        }
    }
    return 0;
}
