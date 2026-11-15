#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 y;
    u8 unknown_02;
    u8 height;
    u16 count;
    u8 unknown_06[0xE];
} MenuLayout;

typedef struct {
    u8 unknown_00[0x80];
    MenuLayout layout;
    u32 *items;
    u8 *enabled;
} MenuPanel;

typedef struct {
    u8 unknown_00[0x480];
    u8 order[6];
} MenuShared;

typedef struct {
    u8 unknown_0000[0x2190];
    u8 phase;
    u8 unknown_2191[0x3C2A - 0x2191];
    u8 entry;
} GlobalState;

typedef struct {
    u8 unknown_00[7];
    u8 locked;
    u8 unknown_08[4];
} TableEntry;

extern MenuShared *data_0200F438;
extern GlobalState g_state_02000000;
extern const TableEntry g_table_08563A70[];

u8 func_080C9540(u16 bit_index);
u8 func_080C95A8(u16 index);
u8 func_08027AE8(void);
void *func_08096D7C(void);
void *func_08099544(void *context);

/* Complete target: [0x08027B2C, 0x08027D10), 484 bytes, 209 instructions.
 *
 * Fills the option list of the mode 1 menu for func_08027DA0, its only
 * caller.  The tests are the ones func_08028FF4 makes for the same option
 * numbers; as there, the ROM calls func_08027AE8 for option 3 and has the
 * pair func_08096D7C, func_08099544 in line for option 5.
 *
 * The doubling is a shift: stored to a u8 it is narrowed to u8 arithmetic,
 * so the count loaded for `height` is reused (`adds r1, r0`).  Written `* 2`
 * it stays an int multiply and the count is loaded a third time.
 */
void func_08027B2C(MenuPanel *panel)
{
    MenuLayout *layout = &panel->layout;
    s32 index;

    panel->items[0] = 1;
    data_0200F438->order[0] = 1;
    index = 1;
    if (func_080C9540(2) != 0) {
        layout->count--;
    } else {
        panel->items[1] = 2;
        data_0200F438->order[1] = 2;
        index = 2;
    }

    if (func_080C9540(2) != 0) {
        layout->count--;
    } else {
        if (func_080C9540(0x207) != 0) {
            panel->items[index] = 3;
        } else {
            panel->items[index] = 7;
        }
        if (func_08027AE8() == 0) {
            panel->enabled[index] = 0;
        }
        data_0200F438->order[index] = 3;
        index++;
    }

    panel->items[index] = 4;
    data_0200F438->order[index] = 4;
    index++;

    if (func_080C9540(2) != 0) {
        layout->count--;
    } else {
        const TableEntry *entry = &g_table_08563A70[g_state_02000000.entry];
        panel->items[index] = 5;
        if (func_08099544(func_08096D7C()) == 0 ||
            g_state_02000000.phase == 2 || entry->locked != 0) {
            panel->enabled[index] = 0;
        }
        data_0200F438->order[index] = 5;
        index++;
    }

    if (func_080C9540(2) != 0) {
        layout->count--;
    } else {
        panel->items[index] = 6;
        data_0200F438->order[index] = 6;
        if (func_080C95A8(13) == 1) {
            panel->enabled[index] = 0;
        }
    }

    layout->height = layout->count;
    if (layout->count <= 5) {
        layout->y += (6 - layout->count) << 1;
    }
}
