#include "ffta.h"

/* Complete [0x080255FC, 0x08025688): 140 bytes, 59 instructions.
 * Target:
 *   30b50006010e0f293dd8184c88008822d2008018226810180023038043800429
 *   2ed11349501803804380124d00228b23db0002212068c0180280428004330139
 *   0029f7da094c00220b4b02212068c01802804280043301390029f7da2a1c9432
 *   11880648084010800de0000038f400025404000090f3000274040000dfff0000
 *   022900d1936130bc01bc0047
 *
 * Clears saved position `index`.  Index 4 also clears entries 5, 6..8 and
 * 13..15 and state flag 0x20; index 2 also clears `selected`.
 *
 * The table is addressed here as 0x440 + 4 * index (`movs #0x88`/`lsls #3`)
 * under `cmp #15`/`bhi`, so it has 16 entries and ends where the 0x480 table
 * of src/08028FF4.c begins.  src/0802800C.c, src/08028B20.c and
 * src/080284A0.c address the same halfword pairs as 0x444 + 4 * window
 * index, which is entry `window index + 1` of this table.
 */
typedef struct {
    s16 top;
    s16 row;
} SavedPosition;

typedef struct {
    u8 unknown_00[0x18];
    u32 selected;
    u8 unknown_1C[0x424];
    SavedPosition positions[16];
} MenuControl;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} MenuState;

extern MenuControl *data_0200F438;
extern MenuState g_state_0200F390;

void func_080255FC(u8 index)
{
    SavedPosition *position;
    s32 i;

    if (index < 16) {
        position = &data_0200F438->positions[index];
        position->top = 0;
        position->row = 0;
        if (index == 4) {
            position = &data_0200F438->positions[5];
            position->top = 0;
            position->row = 0;
            for (i = 0; i < 3; i++) {
                position = &data_0200F438->positions[6 + i];
                position->top = 0;
                position->row = 0;
            }
            for (i = 0; i < 3; i++) {
                position = &data_0200F438->positions[13 + i];
                position->top = 0;
                position->row = 0;
            }
            g_state_0200F390.flags &= ~0x20;
        } else if (index == 2) {
            data_0200F438->selected = 0;
        }
    }
}
