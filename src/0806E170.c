#include "ffta.h"

// Complete target [0x0806E170, 0x0806E298): 296 bytes, 121 instructions.

typedef struct {
    u8 unknown_00[0xC];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 height;
    u8 unknown_17[3];
    u16 top;
    u8 unknown_1C[4];
} MenuList0806E170;

typedef struct {
    u16 item;
    u8 unknown_02;
    u8 unknown_03;
} Item0806E170;

typedef struct {
    u8 unknown_0000[0x1494];
    u8 object[0x2C];
    MenuList0806E170 list;
    u8 controls[0x14];
    u8 unknown_14F4[0x2F79];
    u8 count;
    u8 unknown_446E[0x7E];
    u16 selected_item;
    u8 selected;
    u8 unknown_44EF[0x15];
    Item0806E170 items[0x17C];
    u8 detail[0xA8];
    u8 summary[1];
} State0806E170;

extern State0806E170 *data_0200F428;
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0806E528(void);
extern void func_0806E66C(MenuList0806E170 *list, u16 item, u8 flags,
                          u8 unknown_02, u32 mode, u32 row, u32 option);
extern void func_08017FB0(void *controls, u8 row);
extern void func_0806E4E0(void *object);
extern void func_0806F0D8(void *state, u16 item);
extern void func_0806F3C4(void *state, u16 item);

void func_0806E170(u16 top, u8 row, u8 mode)
{
    MenuList0806E170 *list = &data_0200F428->list;
    u16 zero;
    u8 count;
    u8 i;
    u8 index;

    data_0200F428->selected = row + top;
    data_0200F428->selected_item = data_0200F428->items[data_0200F428->selected].item;
    list->top = top;

    count = data_0200F428->count > 4 ? 4 : data_0200F428->count;

    // Clear the list's tile buffer: CpuSet fill of width * height tiles,
    // counted in halfwords (bytes / 2).
    zero = 0;
    func_0814186C(&zero, list->tiles,
                  0x01000000 | ((u32)(list->width * (list->height << 1)) >> 1));
    func_0806E528();

    i = 0;
    for (index = list->top; i < count; i++, index++) {
        func_0806E66C(list,
                      data_0200F428->items[index].item,
                      data_0200F428->items[index].unknown_03,
                      data_0200F428->items[index].unknown_02, mode, i, 0);
    }

    func_08017FB0(data_0200F428->controls, row);
    func_0806E4E0(data_0200F428->object);
    func_0806E528();
    func_0806F0D8(data_0200F428->detail, data_0200F428->selected_item);
    func_0806F3C4(data_0200F428->summary, data_0200F428->selected_item);
}
