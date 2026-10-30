#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 value_15;
    u8 value_16;
    u8 unknown_17;
    s16 value_18;
    u8 unknown_1A[6];
} MenuListView;

typedef struct {
    u8 unknown_00[0x11];
    s8 value_11;
} MenuControlsView;

typedef struct {
    u8 unknown_000[0xD1C];
    MenuListView list;
    MenuControlsView controls;
} MenuContextView;

extern MenuContextView *data_0200F428;
extern u16 func_08017B50(MenuListView *list);
/* The row word's signed low byte is used by the complete ROM callee. */
extern void func_0802ACD4(MenuListView *list, s32 row_word,
                          u8 value, u8 column, u8 count);

/* Target [0x08052790, 0x08052800), 112 bytes:
 * 70b581b004480068044944182031401800251126865720e028f400021c0d0000
 * b5420bd1607d02380006000e0090201c291c0b220223d8f785fa0be029060916
 * 607d02380006000e0090201cff220223d8f778fa681c0006050e201cc5f7b0f9
 * 0004000c8542dbd301b070bc01bc0047
 */
void func_08052790(void)
{
    MenuListView *list = &data_0200F428->list;
    MenuControlsView *controls = (MenuControlsView *)(list + 1);
    s8 selected = controls->value_11;
    u8 row;

    for (row = 0; row < func_08017B50(list); row++) {
        if (row == selected) {
            func_0802ACD4(list, row, 11, 2, (u8)(list->value_15 - 2));
        } else {
            func_0802ACD4(list, (s8)row, 255, 2, (u8)(list->value_15 - 2));
        }
    }
}
