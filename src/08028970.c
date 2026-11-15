#include "ffta.h"

/* Complete [0x08028970, 0x08028B1E): 430 bytes, 183 instructions, eight
 * literal words in five pools.
 * f0b54f464646c0b4041c0c2000198146271c583710484588868800888046042028400028
 * 1ed0201c383011217956eff7e3f8011c09040914201cfff73bff011c0648026811810804
 * 00280bd0481e1081034810800120a4e00000000338f40002feff00000220284000281bd0
 * 201cfff707ff000600282bd10120692118f1c0fd4846eef7b7f9381c0021eff78df90348
 * 016803480880012083e0000038f40002ffff000001200540002d65d0201c383011217956
 * eff7a0f8084d2a68411c11800004060c201cfff7c5fe0006002807d001206b2118f194fd
 * 002062e038f400022b6819790d1c052d03d11e829869d86136e0881f0006000e022801d9
 * 0f2d15d10949a07a8000401802683004211c94310968801340180068c000121890885861
 * 0f2d1dd11be0000084ba5108022d09d13004211c94310968801340180068586198610de0
 * 081c0d380006000e012807d83004211c943109688013401800681882642018f135fd4846
 * eef744f9381c0021eff71af9012014e0054800684079002808d0201c311cfff707fe0006
 * 000e08e038f40002201c311c4246fff73bfd0006000e18bc9846a146f0bc02bc0847
 */
/* The object and control are those of src/08028584.c and src/080284A0.c
 * (unit, cursor, entries; mode, selected); byte_0A, the eight-byte table
 * records and the mode groups are those of src/08028824.c; the signed status
 * and its "- 1" index are those of src/080287C4.c and src/0802839C.c. */
typedef struct {
    u8 unknown_00[0x20];
} NavigationUnit;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[0x2A];
} NavigationCursor;

typedef struct {
    u8 unknown_00[0x0A];
    u8 byte_0A;
    u8 unknown_0B;
    u8 window[0x2C];
    NavigationUnit unit;
    NavigationCursor cursor;
    u32 *entries;
} NavigationState;

typedef struct {
    s16 status;
    u8 unknown_02[2];
    u8 mode;
    u8 byte_05;
    u8 unknown_06[2];
    u16 value_08;
    u8 unknown_0A[6];
    u16 value_10;
    u8 unknown_12[2];
    u32 value_14;
    u32 selected;
    u32 value_1C;
} NavigationControl;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[4];
    u16 value_04;
    u8 unknown_06[2];
} TableRecord;

extern InputState data_03000000;
extern NavigationControl *data_0200F438;
extern const TableRecord *const g_table_0851BA84[];
extern u16 func_08017B68(NavigationUnit *unit, u32 row);
extern u16 func_08028824(const NavigationState *state, s16 index);
extern u8 func_080287F0(const NavigationState *state);
extern void func_08141570(s32 player_id, u16 song_id);
extern void func_08016D64(void *window);
extern void func_08017D18(NavigationCursor *cursor, u8 mask);
extern u8 func_080287C4(const NavigationState *state);
extern void func_08141540(u16 song_id);
extern s32 func_08028708(NavigationState *state, u16 keys);
extern u32 func_08028584(NavigationState *state, u16 pressed, u16 held);

u8 func_08028970(NavigationState *state)
{
    void *window = state->window;
    NavigationCursor *cursor = &state->cursor;
    u16 pressed = data_03000000.pressed;
    u16 repeated = data_03000000.repeated;
    u16 held = data_03000000.held;

    if (pressed & 4) {
        data_0200F438->value_08 =
            func_08028824(state, func_08017B68(&state->unit, cursor->row));
        if (data_0200F438->value_08) {
            data_0200F438->value_08--;
            data_0200F438->status = -2;
            return 1;
        }
    }
    if (pressed & 2) {
        if (func_080287F0(state)) {
            func_08141570(1, 0x6B);
            return 0;
        }
        func_08141570(1, 0x69);
        func_08016D64(window);
        func_08017D18(cursor, 0);
        data_0200F438->status = -1;
        return 1;
    }
    if (pressed & 1) {
        s16 index;

        data_0200F438->status = func_08017B68(&state->unit, cursor->row) + 1;
        index = data_0200F438->status - 1;
        if (func_080287C4(state)) {
            func_08141570(1, 0x6B);
            return 0;
        }
        if (data_0200F438->mode == 5) {
            data_0200F438->value_10 = index;
            data_0200F438->value_1C = data_0200F438->selected;
        } else if (data_0200F438->mode == 6 || data_0200F438->mode == 7 ||
                   data_0200F438->mode == 8 || data_0200F438->mode == 15) {
            const TableRecord *table = g_table_0851BA84[state->byte_0A];

            table += state->entries[index];
            data_0200F438->value_14 = table->value_04;
            if (data_0200F438->mode == 15)
                data_0200F438->value_10 = data_0200F438->value_14;
        } else if (data_0200F438->mode == 2) {
            data_0200F438->value_14 = state->entries[index];
            data_0200F438->selected = data_0200F438->value_14;
        } else if (data_0200F438->mode == 13 || data_0200F438->mode == 14) {
            data_0200F438->value_10 = state->entries[index];
        }
        func_08141540(0x64);
        func_08016D64(window);
        func_08017D18(cursor, 0);
        return 1;
    }
    return data_0200F438->byte_05 ? func_08028708(state, repeated)
                                  : func_08028584(state, repeated, held);
}
