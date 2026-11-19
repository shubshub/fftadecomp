#include "ffta.h"

/* Complete [0x0804CBB4, 0x0804D5AC): 2552 bytes, including the 27-entry jump
 * table at 0x0804CBDC and the literal pools. */

typedef struct {
    u8 delay;            /* +0x00 */
    u8 enabled;          /* +0x01 */
    u8 mode;             /* +0x02 */
    u8 unknown_03[5];
    u16 current;         /* +0x08 */
    u16 count;           /* +0x0A */
    u16 commands[8];     /* +0x0C */
    void *first;         /* +0x1C */
    void *second;        /* +0x20 */
    void *third;         /* +0x24 */
    void *window;        /* +0x28 */
} CommandState0804CBB4;

typedef struct {
    u32 unknown_00;      /* +0x00 */
    u32 field_04;        /* +0x04 */
    u8 unknown_08[4];
    u16 field_0c;        /* +0x0C */
    u8 unknown_0e[4];
    u8 unknown_12;       /* +0x12 */
} Record0804CBB4;

typedef struct {
    u8 first;
    u8 second;
    u16 count;
} Selection0804CBB4;

extern CommandState0804CBB4 *data_0201F544;
extern Record0804CBB4 g_state_020020D0;
extern Table data_03002710;
extern u8 data_030008B0[];
extern u8 data_03000990[];

extern void *func_0804CA58(u32 bytes);
extern void func_0804CA6C(void *block);
extern void func_0804CABC(void);
extern void func_0804CAD0(void);
extern void func_0804D5AC(u8 enabled);
extern u8 func_0804D5F4(void);
extern void func_0804D658(void);
extern void func_0804D6B0(s16 mode);
extern void func_0804D7E8(void);
extern u8 func_0804D814(void);
extern void func_0804D840(void);
extern void *func_0804E128(u8 selection);
/* The only caller passes 0 (0x0804D59C); src/0804E1B8.c reads no argument. */
extern s32 func_0804E1B8(u8 unused);
extern s16 func_0804E1E0(void *task);
extern void func_0804E1F0(void *task);
extern s32 func_0804E224(void *task);
extern void func_0804E3BC(void *task, u8 enabled);
extern void func_0804E990(void);
extern void func_0804E9A0(void *task);
extern void func_0804E9C4(u32 value);
extern u32 func_0804E9D0(void);
extern void func_0804E9DC(void *task);
extern void func_0804E9F0(void *unused, u8 *state);
extern u8 func_0804ED60(void);
extern u8 func_08050E84(void);
extern void func_08006B8C(Table *table, u8 index);
extern void func_0801174C(void *window, u32 kind, u8 index, void *first,
                          void *second, u32 x, u32 y, u32 width, u32 height,
                          u32 tile);
extern void func_0801339C(u16 value);
extern void func_08013404(void (*first)(void), void (*second)(void));
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08141540(u32 sound);

/* The state stack: PUSH_STATE saves the current state, POP_STATE resumes the
 * last one saved. */
#define PUSH_STATE() \
    (data_0201F544->commands[data_0201F544->count++] = data_0201F544->current)
#define POP_STATE() \
    (data_0201F544->current = data_0201F544->commands[--data_0201F544->count])

u8 func_0804CBB4(void)
{
    s16 result;
    Selection0804CBB4 *selection;
    u8 index;

    switch (data_0201F544->current) {
    case 26:
        func_0804E990();
        return 1;
    case 0:
        data_0201F544->third = func_0804E128(10);
        data_0201F544->delay = 4;
        data_0201F544->current = 1;
        PUSH_STATE();
        data_0201F544->current = 25;
        break;
    case 1:
        data_0201F544->first = func_0804E128(1);
        data_0201F544->second = func_0804E128(2);
        func_0804E9DC(data_0201F544->second);
        data_0201F544->current = 2;
        break;
    case 3:
        data_0201F544->second = func_0804E128(2);
        data_0201F544->delay = 16;
        func_0804E9DC(data_0201F544->second);
        data_0201F544->current = 4;
        break;
    case 4:
        if (data_0201F544->delay != 0) {
            data_0201F544->delay--;
            if (data_0201F544->delay != 0)
                break;
        }
        func_0804E1F0(data_0201F544->first);
        POP_STATE();
        break;
    case 2:
        if (func_0804E1E0(data_0201F544->first) == 0)
            break;
        func_0804D6B0(func_0804E224(data_0201F544->first));
        break;
    case 5:
        result = func_0804E1E0(data_0201F544->second);
        if (result == 0)
            break;
        if (result == -1) {
            func_0804D5AC(2);
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            break;
        }
        func_0804E9C4(func_0804E224(data_0201F544->second));
        data_0201F544->mode = 11;
        g_state_020020D0.unknown_12 = 2;
        func_0804D5AC(7);
        data_0201F544->current = 6;
        PUSH_STATE();
        data_0201F544->current = 23;
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 6:
        if (func_0804E1E0(data_0201F544->second) == 0)
            break;
        func_0804E9A0(data_0201F544->second);
        data_0201F544->third = func_0804E128(10);
        data_0201F544->first = func_0804E128(1);
        data_0201F544->second = func_0804E128(3);
        func_0804E9DC(data_0201F544->first);
        data_0201F544->current = 5;
        break;
    case 7:
        result = func_0804E1E0(data_0201F544->second);
        if (result == 0)
            break;
        if (result == -1) {
            func_0804D5AC(2);
            data_0201F544->delay = 4;
            data_0201F544->current = 1;
            PUSH_STATE();
            data_0201F544->current = 25;
            PUSH_STATE();
            data_0201F544->current = 24;
            break;
        }
        func_0804E9C4(func_0804E224(data_0201F544->second));
        data_0201F544->mode = 11;
        g_state_020020D0.unknown_12 = 3;
        func_0804D5AC(6);
        data_0201F544->current = 8;
        PUSH_STATE();
        data_0201F544->current = 23;
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 8:
        if (func_0804E1E0(data_0201F544->second) == 0)
            break;
        func_0804E9A0(data_0201F544->second);
        data_0201F544->third = func_0804E128(10);
        data_0201F544->second = func_0804E128(8);
        data_0201F544->current = 7;
        break;
    case 9:
        func_08006ADC(&data_03002710, 3, (u32)func_0804E9F0);
        data_0201F544->current = 10;
        break;
    case 10:
        if (func_0804ED60() != 9)
            break;
        func_08006B8C(&data_03002710, 3);
        data_0201F544->current = 0;
        break;
    case 11:
        result = func_0804E1E0(data_0201F544->second);
        if (result == 0)
            break;
        if (result == -1) {
            func_0804D5AC(2);
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            break;
        }
        func_0804E9C4(func_0804E224(data_0201F544->second));
        selection = (Selection0804CBB4 *)func_0804E9D0();
        g_state_020020D0.field_04 = selection->first | 0x10000;
        if (selection->count != 0) {
            g_state_020020D0.unknown_00 = 0;
            g_state_020020D0.field_0c = selection->count;
            index = 4;
        } else {
            index = 0;
        }
        data_0201F544->window = func_0804CA58(0xA04);
        func_0801174C(data_0201F544->window, 1, index, data_030008B0,
                      data_03000990, 2, 2, 24, 4, 0x360);
        func_0801339C(2);
        func_08013404(func_0804CABC, func_0804CAD0);
        func_0804E3BC(data_0201F544->second, 0);
        if (selection->count != 0) {
            PUSH_STATE();
            data_0201F544->current = 13;
        } else {
            PUSH_STATE();
            data_0201F544->current = 12;
        }
        func_0804D5AC(4);
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 12:
        if (func_08011860() == 0)
            break;
        if (func_08013380() != 0) {
            data_0201F544->third = func_0804E128(10);
            func_0804E1F0(data_0201F544->second);
            func_0804CA6C(data_0201F544->window);
            data_0201F544->delay = 4;
            /* Resume the saved state and push it back: the ROM keeps both
             * halves (0x0804D0A6..0x0804D0C4, shared with case 17). */
            POP_STATE();
            PUSH_STATE();
            data_0201F544->current = 25;
        } else {
            data_0201F544->current = 15;
            PUSH_STATE();
            data_0201F544->current = 14;
        }
        func_0804E3BC(data_0201F544->second, 1);
        break;
    case 13:
        if (func_08011860() == 0)
            break;
        func_08141540(100);
        data_0201F544->third = func_0804E128(10);
        func_0804E1F0(data_0201F544->second);
        func_0804CA6C(data_0201F544->window);
        data_0201F544->delay = 4;
        POP_STATE();
        PUSH_STATE();
        data_0201F544->current = 25;
        func_0804E3BC(data_0201F544->second, 1);
        break;
    case 14:
        func_0804D7E8();
        func_0801174C(data_0201F544->window, 1, 11, data_030008B0,
                      data_03000990, 2, 2, 24, 4, 0x360);
        func_0801339C(2);
        func_08013404(func_0804CABC, func_0804CAD0);
        func_0804E3BC(data_0201F544->second, 0);
        POP_STATE();
        break;
    case 15:
        if (func_08011860() == 0)
            break;
        data_0201F544->third = func_0804E128(10);
        func_0804CA6C(data_0201F544->window);
        func_0804D5AC(2);
        data_0201F544->mode = 4;
        data_0201F544->delay = 4;
        if (func_0804D814() == 0) {
            /* Restart the stack with 2, 3, 24 and run 25.  The ROM stores
             * only the final values (0x0804D1E8..0x0804D1FA): the count of 3
             * lands between commands[1] and commands[2], and 24 is loaded
             * where the state is set to it, ahead of the count store. */
            data_0201F544->count = 0;
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            PUSH_STATE();
            data_0201F544->current = 25;
            break;
        }
        data_0201F544->current = 23;
        PUSH_STATE();
        data_0201F544->current = 24;
        PUSH_STATE();
        data_0201F544->current = 25;
        break;
    case 16:
        result = func_0804E1E0(data_0201F544->second);
        if (result == 0)
            break;
        if (result == -1) {
            func_0804D5AC(2);
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            break;
        }
        func_0804E9C4(func_0804E224(data_0201F544->second));
        g_state_020020D0.field_04 = func_0804E9D0() | 0x20000;
        data_0201F544->window = func_0804CA58(0xA04);
        func_0801174C(data_0201F544->window, 1, 0, data_030008B0,
                      data_03000990, 2, 2, 24, 4, 0x360);
        func_0801339C(2);
        func_08013404(func_0804CABC, func_0804CAD0);
        func_0804E3BC(data_0201F544->second, 0);
        PUSH_STATE();
        data_0201F544->current = 17;
        func_0804D5AC(4);
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 17:
        if (func_08011860() == 0)
            break;
        if (func_08013380() != 0) {
            data_0201F544->third = func_0804E128(10);
            func_0804E1F0(data_0201F544->second);
            func_0804CA6C(data_0201F544->window);
            data_0201F544->delay = 4;
            POP_STATE();
            PUSH_STATE();
            data_0201F544->current = 25;
        } else {
            data_0201F544->current = 19;
            PUSH_STATE();
            data_0201F544->current = 18;
        }
        func_0804E3BC(data_0201F544->second, 1);
        break;
    case 18:
        func_0804D840();
        func_0801174C(data_0201F544->window, 1, 11, data_030008B0,
                      data_03000990, 2, 2, 24, 4, 0x360);
        func_0801339C(2);
        func_08013404(func_0804CABC, func_0804CAD0);
        func_0804E3BC(data_0201F544->second, 0);
        POP_STATE();
        break;
    case 19:
        if (func_08011860() == 0)
            break;
        data_0201F544->third = func_0804E128(10);
        func_0804CA6C(data_0201F544->window);
        func_0804D5AC(2);
        data_0201F544->mode = 5;
        data_0201F544->delay = 4;
        if (func_08050E84() == 0) {
            data_0201F544->count = 0;
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            PUSH_STATE();
            data_0201F544->current = 25;
        } else {
            data_0201F544->current = 23;
            PUSH_STATE();
            data_0201F544->current = 24;
            PUSH_STATE();
            data_0201F544->current = 25;
        }
        func_0804E3BC(data_0201F544->second, 1);
        break;
    case 20:
        result = func_0804E1E0(data_0201F544->second);
        if (result == 0)
            break;
        if (result == -1) {
            func_0804D5AC(2);
            data_0201F544->current = 2;
            PUSH_STATE();
            data_0201F544->current = 3;
            PUSH_STATE();
            data_0201F544->current = 24;
            break;
        }
        func_0804E9C4(func_0804E224(data_0201F544->second));
        data_0201F544->mode = 7;
        func_0804D5AC(3);
        data_0201F544->current = 21;
        PUSH_STATE();
        data_0201F544->current = 23;
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 21:
        if (func_0804E1E0(data_0201F544->second) == 0)
            break;
        func_0804D5AC(2);
        data_0201F544->current = 22;
        PUSH_STATE();
        data_0201F544->current = 24;
        break;
    case 22:
        data_0201F544->first = func_0804E128(1);
        data_0201F544->second = func_0804E128(6);
        func_0804E9DC(data_0201F544->first);
        data_0201F544->current = 20;
        break;
    case 23:
        data_0201F544->second = func_0804E128(data_0201F544->mode);
        POP_STATE();
        break;
    case 24:
        if (func_0804D5F4() == 0)
            break;
        func_0804D658();
        POP_STATE();
        break;
    case 25:
        if (data_0201F544->delay != 0) {
            data_0201F544->delay--;
            if (data_0201F544->delay != 0)
                break;
        }
        POP_STATE();
        break;
    }
    func_0804E1B8(0);
    return 0;
}
