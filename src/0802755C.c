#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u8 unknown_06[0x0e];
} Layout0802755C;

typedef struct {
    u8 unknown_00[0x80];
    Layout0802755C layout;
    u32 *entries;
    u8 *enabled;
    u8 unknown_9c[4];
    void *allocation;
} ListState0802755C;

typedef struct {
    u8 unknown_00[0x1f3c];
    u8 selections[20][2];
} SelectionState0802755C;

/* The object at 0x02002FC4 as src/08063060.c has it: the ROM adds 0xc70 to a
   register holding 0x02002FC4 to reach the list (0x0802760E, 0x0802765C,
   0x080276C6), and 0x08063094 reaches the capacity byte as that base plus
   0xc6e. */
typedef struct {
    u8 unknown_00[0xc6e];
    u8 capacity;
    u8 count;
    u16 entries[4];
} Roster0802755C;

typedef struct {
    u8 value;
    u8 unknown_01[15];
} BaseEntry0802755C;

extern SelectionState0802755C g_state_02000000;
extern Roster0802755C g_state_02002FC4;
extern const BaseEntry0802755C g_table_08528F34[];
extern const u8 data_08391448[];

extern void *func_08005B28(u32 byte_count);
extern u8 func_0802D764(void);

/* Complete target: [0x0802755C, 0x08027750), 500 bytes, 223 instructions. */
void func_0802755C(ListState0802755C *state)
{
    Layout0802755C *layout = &state->layout;
    Roster0802755C *roster = &g_state_02002FC4;
    u8 used;
    s32 count;
    s32 i;
    s32 j;
    u8 id;
    u8 found;

    state->allocation = func_08005B28(0x80);
    used = func_0802D764();
    count = 0;
    for (i = 0; i < 20; i++) {
        id = g_state_02000000.selections[i][0];

        if (id == 0)
            continue;
        state->entries[i] = id;
        if (used == roster->capacity && id <= 0x55) {
            state->enabled[i] = 0;
        } else if (used == 0 && id > 0x55) {
            state->enabled[i] = 0;
        } else {
            found = 0;
            if (id <= 0x55) {
                for (j = 0; j < roster->capacity; j++) {
                    if (roster->entries[j] != 0 &&
                        roster->entries[j] == id) {
                        found = 1;
                        break;
                    }
                }
                if (found)
                    state->enabled[i] = 0;
            } else if (id >= 0x56 && id <= 0xaa) {
                for (j = 0; j < roster->capacity; j++) {
                    if (roster->entries[j] != 0 &&
                        roster->entries[j] == id - 0x55) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    state->enabled[i] = 0;
            } else if (id >= 0xab && id <= 0xb0) {
                for (j = 0; j < roster->capacity; j++) {
                    if (roster->entries[j] != 0 &&
                        (g_table_08528F34 + roster->entries[j])->value == id - 0xaa) {
                        found = 1;
                        break;
                    }
                }
                if (!found)
                    state->enabled[i] = 0;
            }
        }
        count++;
    }

    layout->count = count;
    if (layout->count <= 5) {
        layout->height = layout->count;
        layout->y = data_08391448[layout->count - 1];
    }
    if (layout->count <= 6)
        layout->x++;
}
