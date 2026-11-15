#include "ffta.h"

/* Complete [0x08081DEC, 0x08081FB0): 452 bytes, 191 instructions. */
typedef struct {
    u16 id;
    u16 flags;
    u8 unknown_04[8];
    u16 value;
    u8 unknown_0E[6];
} MenuEntry;

typedef struct {
    u8 unknown_00[0x18];
    MenuEntry *entries;
} EntryTable;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x38];
    u16 value;
    u8 unknown_3A[4];
    u16 action;
    u16 selected_id;
    u8 unknown_42[6];
    EntryTable *primary;
    u8 unknown_4C[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 unknown_AC[0x1C];
    EntryTable *secondary;
} MenuRecord;

typedef struct {
    u8 unknown_0000[0x2C88];
    MenuRecord records[0];
} MenuState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern InputState data_03000000;
extern MenuState *data_03002818;
extern u16 func_08017B68(MenuList *list, u32 row);
extern u16 func_08017B50(MenuList *list);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_08141540(u16 song_id);
extern void func_08081D28(u32 index, u8 option, s8 row, u8 refresh);

/* The target forms the cursor's address (record + 0x98) at each of its four
 * reads and loads row from it at +0x11. */
#define RECORD_CURSOR(index) (&data_03002818->records[index].cursor)

s32 func_08081DEC(u32 index)
{
    if (data_03000000.pressed == 4) {
        s8 selected = func_08017B68(&data_03002818->records[index].list, RECORD_CURSOR(index)->row);

        if ((data_03002818->records[index].value =
             data_03002818->records[index].primary->entries[selected].value) != 0)
            return 10;
        func_08141540(0x6A);
    }
    if (data_03000000.pressed == 1) {
        EntryTable *table = data_03002818->records[index].secondary;
        s8 row = RECORD_CURSOR(index)->row;
        u16 selected = func_08017B68(&data_03002818->records[index].list, row);

        if (!(table->entries[selected].flags & 1)) {
            data_03002818->records[index].selected_id = table->entries[selected].id;
            data_03002818->records[index].action = 1;
        }
    }
    if (data_03000000.pressed == 2)
        data_03002818->records[index].action = 2;

    if (data_03000000.repeated == 0x80) {
        s8 row = RECORD_CURSOR(index)->row + 1;

        if (row < func_08017B50(&data_03002818->records[index].list)) {
            func_08081D28(index, 0x80, row, 0);
        } else if (func_08017A90(&data_03002818->records[index].list, 0x80)) {
            func_08081D28(index, 0x80, row, 1);
            return 7;
        }
    } else if (data_03000000.repeated == 0x40) {
        s8 row = RECORD_CURSOR(index)->row - 1;

        if (row < 0) {
            if (func_08017A90(&data_03002818->records[index].list, 0x40)) {
                func_08081D28(index, 0x40, row, 1);
                return 7;
            }
        } else {
            func_08081D28(index, 0x40, row, 0);
        }
    }
    return 6;
}
