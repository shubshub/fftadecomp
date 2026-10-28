#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Cursor080837AC;

typedef struct {
    u8 unknown_00[0x36];
    u8 selection;
    u8 unknown_37[0x41];
    u8 list[0x20];
    Cursor080837AC cursor;
    u8 settings[0x20];
} Slot080837AC;

typedef struct {
    u8 unknown_0000[0x2c88];
    Slot080837AC slots[1];
} State080837AC;

extern State080837AC *data_03002818;
extern void func_08017FBC(void *settings, u32 direction);
extern void func_08080F68(void *list, s32 row, u32 x, u32 y);
extern void func_08017FB0(Cursor080837AC *cursor, u8 row);
extern u16 func_08017B68(void *list, s32 row);
extern void func_080835A4(u32 index, s32 row, void *list);
extern void func_08017884(void *list, u32 direction, u32 mode);

/* Complete target [0x080837AC, 0x0808389C): 240 bytes, 101 instructions. */
void func_080837AC(u32 index, u8 direction, u8 row, u8 refresh)
{
    func_08017FBC(data_03002818->slots[index].settings, direction);
    if (!refresh) {
        s8 selected = row;

        func_08080F68(data_03002818->slots[index].list, selected, 11, 11);
        func_08017FB0(&data_03002818->slots[index].cursor, (u8)selected);
        data_03002818->slots[index].selection =
            func_08017B68((u8 *)data_03002818 + index * sizeof(Slot080837AC) + 0x2d00,
                          selected);
    } else {
        s8 selected = row;

        func_080835A4(index, selected, data_03002818->slots[index].list);
        data_03002818->slots[index].selection =
            func_08017B68((u8 *)data_03002818 + index * sizeof(Slot080837AC) + 0x2d00,
                          selected);
        func_08017884(data_03002818->slots[index].list, direction, 1);
        func_08080F68(data_03002818->slots[index].list,
                      (s8)data_03002818->slots[index].cursor.row, 11, 11);
    }
}
