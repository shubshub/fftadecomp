#include "ffta.h"

typedef struct {
    u8 unknown_000[0x424];
    s32 entries[64];
    u32 secondary_ids[0];
} MenuData;

typedef struct {
    MenuData *data;
    u16 flags;
    s16 selection;
    u8 type;
} MenuState;

extern MenuState *func_08005BFC(void *task);
extern const u16 g_table_08529EE4[];

s32 func_0804E224(void *task)
{
    MenuState *state = func_08005BFC(task);
    s16 index = state->selection - 1;

    switch (state->type) {
    case 1:
        if (state->selection == -1)
            return state->selection;
        switch (state->data->secondary_ids[index]) {
        case 0x3B: return 1;
        case 0x3C: return 2;
        case 0x3D: return 3;
        case 0x3E: return 4;
        case 0x4F: return 5;
        case 0x3F: return 6;
        default: return -1;
        }
    case 5:
        return (u16)state->data->entries[index];
    case 3:
    case 4:
    case 6:
        return state->data->entries[index];
    case 8:
        return g_table_08529EE4[index];
    default:
        return 0;
    }
}
