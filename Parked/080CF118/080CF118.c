#include "ffta.h"

typedef struct {
    u8 kind;
    u8 value;
    u16 identifier;
} BindingRecord;

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

typedef struct {
    u8 unknown_00[0x16];
    u16 identifier;
    u8 unknown_18[0x10];
    u16 flags;
} SceneFields;

extern const u8 g_table_0855AE4C[][70];
extern BindingRecord g_state_02002B08[];
extern State g_state_02000080;
extern u8 g_state_02002E34[][6];

void func_080CF118(u8 *data, u8 enabled)
{
    const u8 *definition = g_table_0855AE4C[data[0] | ((data[1] & 3) << 8)];
    u32 processed = 0;
    s32 slot;
    s32 index;

    for (slot = 0; slot < 2; slot++) {
        if (data[slot + 4] != 0) {
            for (index = 0; index < 64; index++) {
                BindingRecord *record = &g_state_02002B08[index];

                if (record->kind == data[slot + 4] &&
                    record->identifier == (data[0] | ((data[1] & 3) << 8))) {
                    record->identifier = 0;
                    record->value = 0;
                    if (enabled) {
                        if (definition[0x36] == record->kind) {
                            u16 flags = definition[0x41] | (definition[0x42] << 8);

                            if ((flags & 0x10) && !(processed & 0x0F)) {
                                (*(void (**)(void *, s32))0x0836D4B8)(record, sizeof(*record));
                                processed |= 0x0F;
                            }
                        }
                        if (definition[0x37] == record->kind) {
                            u16 flags = definition[0x41] | (definition[0x42] << 8);

                            if ((flags & 0x20) && !(processed & 0xF0)) {
                                (*(void (**)(void *, s32))0x0836D4B8)(record, sizeof(*record));
                                processed |= 0xF0;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    data[5] = 0;
    data[4] = 0;

    for (index = 0; index < 24; index++) {
        SceneFields *record = (SceneFields *)&g_state_02000080.first[index];

        if (record->identifier == (data[0] | ((data[1] & 3) << 8))) {
            record->identifier = 0;
            record->flags &= ~4;
        }
    }
    if ((definition[2] & 7) == 1) {
        u8 *selected;

        for (slot = 0; slot < 5; slot++) {
            selected = g_state_02002E34[slot];
            if ((selected[4] | ((selected[5] & 1) << 8)) ==
                (data[0] | ((data[1] & 3) << 8)))
                break;
        }
        selected[2] |= 0x40;
        selected[4] = 0;
        selected[5] &= ~1;
        if (selected[2] & 0x20)
            (*(void (**)(void *, s32))0x0836D4B8)(selected, 6);
    }
}
