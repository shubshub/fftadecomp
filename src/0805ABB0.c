#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_000[0xD20];
    MenuList list;
    MenuControls controls;
    u8 cursor[0x10];
} MenuState;

extern MenuState *data_0200F428;
extern u16 data_03000000;
extern u8 g_state_02000000[];
extern const u32 g_table_085567F0[];
extern void func_08017FBC(void *cursor, u32 direction);
extern u16 func_08017B68(MenuList *list, s8 row);
extern u32 func_080CCB68(u8 index);
extern void func_0805C3D4(u32 value, MenuList *list, u8 row, u32 mode);
extern void func_08017884(MenuList *list, u32 direction, u32 enabled);

// Complete target: [0x0805ABB0, 0x0805AD30), 384 bytes.
// Each 16-byte record at 0x02002E78 holds a unit word and a recruit flag at +4.
void func_0805ABB0(void)
{
    MenuControls *controls = &data_0200F428->controls;
    u8 row = controls->row;
    u8 selected;
    const u8 *state;
    const u8 *record;

    if (data_03000000 & 0x40) {
        row--;
        func_08017FBC(data_0200F428->cursor, 0x40);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        state = g_state_02000000;
        record = state + selected * 16;
        if (*(const u32 *)(record + 0x2E78))
            func_0805C3D4(func_080CCB68(selected), &data_0200F428->list, row, 0);
        else if ((g_state_02000000 + 0x2E7C)[selected * 16])
            func_0805C3D4(func_080CCB68(selected), &data_0200F428->list, row, 4);
        else
            func_0805C3D4(g_table_085567F0[0x26], &data_0200F428->list, row, 0);
        func_08017884(&data_0200F428->list, 0x40, 1);
    } else if (data_03000000 & 0x80) {
        row++;
        func_08017FBC(data_0200F428->cursor, 0x80);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        state = g_state_02000000;
        record = state + selected * 16;
        if (*(const u32 *)(record + 0x2E78))
            func_0805C3D4(func_080CCB68(selected), &data_0200F428->list, row, 0);
        else if ((g_state_02000000 + 0x2E7C)[selected * 16])
            func_0805C3D4(func_080CCB68(selected), &data_0200F428->list, row, 4);
        else
            func_0805C3D4(g_table_085567F0[0x26], &data_0200F428->list, row, 0);
        func_08017884(&data_0200F428->list, 0x80, 1);
    }
}
