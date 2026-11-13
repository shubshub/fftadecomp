#include "ffta.h"

typedef struct {
    u8 unknown_00[0x17];
    u8 unknown_17;
    u16 count;
    u16 unknown_1A;
    u16 unknown_1C;
    u8 unknown_1E[2];
} MenuList;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    u8 unknown_04[4];
    u16 unknown_08;
    u8 unknown_0A[10];
} MenuItem;

typedef struct {
    u8 unknown_00[4];
    u32 **unknown_04;
    u8 unknown_08[0x10];
    MenuItem *unknown_18;
} MenuLayout;

typedef struct {
    u8 unknown_00[0x10];
    u8 *unknown_10;
    u8 unknown_14[0x1C];
    u16 unknown_30;
    u8 unknown_32[0x46];
    MenuList list;
    u8 unknown_98[0x30];
    MenuLayout *unknown_C8;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x68C];
    u8 text_state[0x25FC];
    MenuRecord records[0];
} MenuState;

typedef struct {
    u8 unknown_00[0x4A];
    s8 unknown_4A;
    u8 unknown_4B;
} MenuEntry;

extern MenuState *data_03002818;
extern MenuEntry data_030009E0[];
extern u16 func_08017B68(MenuList *list, u32 index);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08015110(void *state, void *tiles, const void *text,
                          u32 style, u32 spacing);

/* Complete target [0x080819F0,0x08081B24), 308 bytes. */
void func_080819F0(u32 index, u16 row)
{
    MenuLayout *layout = data_03002818->records[index].unknown_C8;
    u16 slot = data_03002818->records[index].unknown_30;
    u16 width = data_030009E0[slot].unknown_4A;
    MenuList *list = (MenuList *)(index * sizeof(MenuRecord) + (u32)data_03002818 + 0x2D00);
    s16 target = (s8)row + list->unknown_1A;
    s32 clamped;
    u8 *destination;
    u32 zero;
    u16 entry;
    u16 offset;
    u32 mode;
    u32 *text;

    if (target < 0)
        clamped = 0;
    else if (target > (s16)list->count - 1)
        clamped = list->count - 1;
    else
        clamped = (u16)target;

    offset = (u16)((u16)clamped % list->unknown_17) * (width << 1)
             + list->unknown_1C;
    destination = data_03002818->records[index].unknown_10 + (offset << 5);
    zero = 0;
    func_08141868(&zero, destination, 0x1000000 | (width << 4));

    entry = func_08017B68(&data_03002818->records[index].list, (s8)row);
    if (layout->unknown_18[entry].unknown_02 == 0)
        mode = 0;
    else
        mode = layout->unknown_18[entry].unknown_02 & 1;
    text = layout->unknown_04[layout->unknown_18[entry].unknown_08];
    func_08015110(data_03002818->text_state, destination, text, mode, 1);
}
