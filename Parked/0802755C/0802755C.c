#include "ffta.h"

typedef struct {
    u8 flags;
    u8 height;
    u8 unknown_02;
    u8 visible_count;
    u16 count;
    u8 unknown_06[0x0e];
} ListOptions0802755C;

typedef struct {
    u8 unknown_00[0x80];
    ListOptions0802755C options;
    u32 *entries;
    u8 *available;
    u8 unknown_9c[4];
    void *resource;
} ListState0802755C;

typedef struct {
    u8 unknown_00[0x1f3c];
    u8 choices[20][2];
} ChoiceState0802755C;

typedef struct {
    u8 unknown_00[0xc70];
    u16 entries[255];
} Roster0802755C;

extern ChoiceState0802755C g_state_02000000;
extern Roster0802755C g_state_02002FC4;
extern u8 data_02003C32;
extern u8 g_table_08528F34[][16];
extern u8 data_08391448[];

void *func_08005B28(u32 size);
u8 func_0802D764(void);

void func_0802755C(ListState0802755C *state)
{
    ListOptions0802755C *options = &state->options;
    u8 mode;
    s32 count;
    s32 i;
    s32 j;
    u8 id;
    u8 found;

    state->resource = func_08005B28(0x80);
    mode = func_0802D764();
    count = 0;
    for (i = 0; i < 20; i++) {
        id = g_state_02000000.choices[i][0];

        if (id == 0)
            continue;
        state->entries[i] = id;
        if (mode == data_02003C32 && id <= 0x55) {
            state->available[i] = 0;
        } else if (mode == 0 && id > 0x55) {
            state->available[i] = 0;
        } else {
            found = 0;
            if (id <= 0x55) {
                for (j = 0; j < data_02003C32; j++) {
                    if (g_state_02002FC4.entries[j] != 0 &&
                        g_state_02002FC4.entries[j] == id) {
                        found = 1;
                        break;
                    }
                }
                if (found)
                    state->available[i] = 0;
            } else if ((u8)(id - 0x56) <= 0x54) {
                for (j = 0; j < data_02003C32; j++) {
                    if (g_state_02002FC4.entries[j] != 0 &&
                        g_state_02002FC4.entries[j] == id - 0x55) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    state->available[i] = 0;
            } else if ((u8)(id + 0x55) <= 5) {
                for (j = 0; j < data_02003C32; j++) {
                    if (g_state_02002FC4.entries[j] != 0 &&
                        g_table_08528F34[g_state_02002FC4.entries[j]][0] == id - 0xaa) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    state->available[i] = 0;
            }
        }
        count++;
    }

    options->count = count;
    if (options->count <= 5) {
        options->visible_count = options->count;
        options->height = data_08391448[options->count - 1];
    }
    if (options->count <= 6)
        options->flags++;
}
