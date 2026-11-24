#include "ffta.h"

/* Complete target [0x08030200, 0x08030E50): 3152 bytes, 711 instructions,
 * including the 255-word jump table at 0x0803021C and the literal pools.
 * The scene handler for game mode 1 (func_08003660 installs it in slot 1 of
 * the mode table at 0x03000830); src/0803172C.c is a sibling handler of the
 * same unit. */

/* The slot entries, as src/080301B0.c declares them. */
typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
} __attribute__((packed)) Resource08030200;

/* A 6-byte record of the table at 0x21E of the display state; the 9-bit id
 * at bytes 4-5 is read a byte at a time (0x080308F4/0x080308F6), and
 * src/080D2EB4.c declares the same record. */
typedef struct {
    u8 unknown_00[4];
    u16 id : 9;
    u16 unknown_04_9 : 7;
} __attribute__((packed)) Record08030200;

/* Byte 0 bit 0 is active as src/0803172C.c names it; bits 7-8 are one field,
 * cleared by a single halfword and with 0xFFFFFE7F (0x0803079A-0x080307A0). */
typedef struct {
    u16 active : 1;
    u16 flag_02 : 1;
    u16 unknown_00_2 : 5;
    u16 unknown_00_7 : 2;
    u16 unknown_01_1 : 7;
    u8 unknown_02[0x1C];
    u16 unknown_1E;
    u16 item;
    u16 unknown_22;
    Resource08030200 *slots[16];
    u8 unknown_64;
    u8 unknown_65;
    u8 unknown_66[0x26];
    u8 unknown_8C;
    u8 unknown_8D;
    u8 unknown_8E_0 : 5;
    u8 flag_8E_20 : 1;
    u8 unknown_8E_6 : 2;
    u8 unknown_8F[0x15];
    u16 unknown_A4;
    u8 unknown_A6[3];
    u8 mode;
    u8 selection;
    u8 unknown_AB;
    u8 unknown_AC;
    u8 unknown_AD;
} Display08030200;

typedef struct {
    Display08030200 *current, *display;
    u8 unknown_08[0x78];
    u8 busy, phase;
    u8 unknown_82[2];
    u8 unknown_84;
    u8 unknown_85[0x19];
    u16 timer;
} State08030200;

/* One 4-byte effect of a 0x46-byte row, as src/080D1E70.c declares it. */
typedef struct {
    u16 index;
    u8 operation;
    s8 operand;
} __attribute__((packed)) ItemEffect08030200;

/* One 0x46-byte row: the effects at 0x12 as src/080D1E70.c declares them,
 * the halfword at 0x41 as src/080D2E78.c does. */
typedef struct {
    u8 unknown_00[0x12];
    ItemEffect08030200 effects[4];
    u8 unknown_22[0x1F];
    u16 flags;
    u8 unknown_43[3];
} __attribute__((packed)) ItemMetadata08030200;

typedef struct {
    u8 unknown_00[0x14];
    u8 unknown_14;
    u8 unknown_15;
} Selection08030200;

typedef struct {
    u16 count;
    u16 unknown_02;
    void *entries;
} List08030200;

extern State08030200 *g_state_03002810;
extern const ItemMetadata08030200 g_table_0855AE4C[];
extern Selection08030200 g_state_020020D0;
extern List08030200 data_03000E30;
extern Table data_03002720, data_03000880;
extern u32 data_030009B0[];
extern u8 data_03000EC8[];
extern void *data_0200F38C;
extern u8 g_state_0200F390[];
extern void *data_03002778;
extern u32 data_03000E54;
extern void *data_030027F4;
extern u8 g_state_02002FC4[];
extern u8 data_0200F388, data_0200F389;

extern void func_08031060(void);
extern void func_08030E50(void);
extern void func_08031348(void);
extern void func_08030088(u32 mode);
extern void func_08006A7C(void *, u32 *, u8 *, u8);
extern void func_08031698(void);
extern void func_08031714(void);
extern void func_080312A8(void);
extern void func_080312CC(void);
extern void func_08034E34(void);
extern void *func_080D2DE0(u16 id);
extern void func_080D1E70(void *item, u16 enabled);
extern u8 func_080C95A8(u16 index);
extern u8 func_08036034(u8, u8);
extern void func_08141708(void);
extern void func_08030168(void);
extern void func_08009AFC(u16 event);
extern u16 func_080038E8(u16 value);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern void func_0804C834(void *entries, s32 count);
extern void func_08141748(u16 interval);
extern void func_080316D0(void);
extern void func_08006B5C(void *);
extern void func_08031264(void);
extern void *func_080070C8(void *storage, u32 size);
extern void *func_08007138(void *owner, u32 size);
extern u16 func_08003900(u16 value, u32 mode);
extern void func_08137B20(void *resource, u8 mode);
extern void func_080038C8(u16 value);
extern void func_080069F4(void *, u8);
extern void func_0804BDDC(u8 period, u8 phase);
extern void func_0800718C(void *);
extern void func_0803155C(u8, u8 *);
extern void func_0808B288(u8, u8 *);
extern void func_0803197C(u8, u8 *);

void func_08030200(u8 index, u8 *state)
{
    switch (*state) {
    case 1:
        func_08031060();
        func_08030E50();
        func_08031348();
        func_08030088(1);
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08031698();
        g_state_03002810->unknown_84 = 0;
        g_state_03002810->display->flag_8E_20 = 0;
        g_state_03002810->display->unknown_8C = 0;
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        *state = 2;
        break;
    case 0:
        func_08031060();
        func_08030E50();
        func_08031348();
        func_08030088(0);
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08031698();
        g_state_03002810->unknown_84 = 0;
        g_state_03002810->display->unknown_A4 = 0;
        g_state_03002810->display->mode = 0;
        g_state_03002810->display->item = 0;
        g_state_03002810->display->unknown_64 = 0;
        g_state_03002810->display->unknown_65 = 0;
        g_state_03002810->display->flag_8E_20 = 1;
        g_state_03002810->display->unknown_8C = 3;
        g_state_020020D0.unknown_14 = 0x80;
        g_state_020020D0.unknown_15 = 0;
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        *state = 2;
        break;
    case 2:
        func_08031714();
        g_state_03002810->display->unknown_8D = 0;
        g_state_03002810->display->active = 0;
        g_state_03002810->busy = 0;
        g_state_03002810->unknown_84 = 0;
        *state = 0xF;
        break;
    case 12:
        func_08031714();
        g_state_03002810->display->active = 0;
        g_state_03002810->busy = 0;
        g_state_03002810->unknown_84 = 0x38;
        *state = 0xF;
        break;
    case 3:
        func_08031060();
        func_080312A8();
        func_08030E50();
        func_08031348();
        func_08030088(1);
        func_08031698();
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        g_state_03002810->display->unknown_00_7 = 0;
        g_state_03002810->display->flag_8E_20 = 0;
        g_state_03002810->display->flag_02 = 0;
        if (g_state_03002810->display->mode == 0) {
            func_08034E34();
            *state = 2;
        } else if (g_state_03002810->display->mode == 1) {
            const ItemMetadata08030200 *metadata;

            func_080D1E70(func_080D2DE0(g_state_03002810->display->item), 1);
            metadata = &g_table_0855AE4C[g_state_03002810->display->item];
            if (metadata->effects[0].index == 0x680) {
                g_state_03002810->display->flag_8E_20 = 1;
                g_state_03002810->display->unknown_8C = func_080C95A8(0x80);
            }
            g_state_03002810->display->unknown_AC = func_08036034(0, 1);
            g_state_03002810->display->unknown_A4 = 0;
            g_state_03002810->display->mode = 0;
            *state = 2;
        } else {
            func_08141708();
            if (g_state_03002810->display->mode != 3 && g_state_03002810->display->unknown_1E != 0) {
                const ItemMetadata08030200 *metadata =
                    &g_table_0855AE4C[g_state_03002810->display->slots[g_state_03002810->display->unknown_1E]->id];

                if (metadata->flags & 0x800) {
                    *state = 2;
                    break;
                }
            }
            if (g_state_03002810->display->mode == 2) {
                g_state_03002810->display->unknown_AD = g_state_03002810->display->mode;
                *state = 2;
            } else if (g_state_03002810->display->mode == 4) {
                /* The record address is the byte sum current + selection * 6
                 * + 0x21E, in that order: current is loaded first
                 * (0x080308E0), the scaled selection is added to it
                 * (0x080308EE) and 0x21E last (0x080308F2).  An index
                 * &current->records[selection] adds 0x21E to the scaled
                 * selection first, as 0x080483E4-0x080483EE does for the same
                 * table, so this arm is written as the byte sum. */
                Display08030200 *current = g_state_03002810->current;
                Record08030200 *record = (Record08030200 *)((u8 *)current
                    + g_state_03002810->display->selection * sizeof(Record08030200) + 0x21E);

                g_state_03002810->display->item = record->id;
                g_state_03002810->display->unknown_22 = 0xFFFF;
                g_state_03002810->display->unknown_AD = g_state_03002810->display->mode;
                *state = 2;
            } else if (g_state_03002810->display->mode == 5) {
                /* A copy of the mode 4 arm (0x08030924-0x08030958). */
                Display08030200 *current = g_state_03002810->current;
                Record08030200 *record = (Record08030200 *)((u8 *)current
                    + g_state_03002810->display->selection * sizeof(Record08030200) + 0x21E);

                g_state_03002810->display->item = record->id;
                g_state_03002810->display->unknown_22 = 0xFFFF;
                g_state_03002810->display->unknown_AD = g_state_03002810->display->mode;
                *state = 2;
            } else if (g_state_03002810->display->mode == 3) {
                g_state_03002810->display->unknown_AC = func_08036034(1, 3);
                g_state_03002810->display->unknown_AD = g_state_03002810->display->mode;
                func_08030168();
                *state = 2;
            }
        }
        break;
    case 6:
        func_08031060();
        func_080312CC();
        func_08030E50();
        func_08031348();
        func_08030088(1);
        func_08031698();
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        *state = 12;
        break;
    case 5:
    case 8:
    case 9:
        func_08031060();
        func_080312CC();
        func_08030E50();
        func_08031348();
        func_08030088(1);
        func_08031698();
        func_08006A7C(&data_03002720, data_030009B0, data_03000EC8, 5);
        func_08006ADC(&data_03000880, 0, (u32)func_0803155C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        *state = 2;
        break;
    case 10:
        func_08009AFC(0xAC);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 15:
        func_08006ADC(&data_03002720, 0, (u32)func_0803197C);
        g_state_03002810->phase = 11;
        *state = 11;
        break;
    case 16:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08009AFC(0xA4);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 17:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08009AFC(0xA6);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 18:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08009AFC(0xA3);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 19:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08009AFC(0xA5);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 20:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08009AFC(0xA2);
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 21:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_080038E8(8);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 23:
        func_0804C834(data_03000E30.entries, 0x40);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_08031060();
        func_08031264();
        func_08031060();
        func_08031264();
        data_0200F38C = func_080070C8(g_state_0200F390, 0xC640);
        /* The work buffer and its size, set as src/080245DC.c sets them: the
         * buffer's address is loaded ahead of the call (0x08030C04). */
        {
            void **buffer = &data_03002778;
            u32 size = 0xC600;

            *buffer = func_08007138(data_0200F38C, size);
            data_03000E54 = size;
        }
        data_030027F4 = g_state_02002FC4;
        func_08003900(10, 1);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 22:
        func_08141748(3);
        func_0804C834(data_03000E30.entries, 0x40);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        data_0200F38C = func_080070C8(g_state_0200F390, 0xC640);
        /* The work buffer and its size, set as src/080245DC.c sets them: the
         * buffer's address is loaded ahead of the call (0x08030C76). */
        {
            void **buffer = &data_03002778;
            u32 size = 0xC600;

            *buffer = func_08007138(data_0200F38C, size);
            data_03000E54 = size;
        }
        func_080038E8(3);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 24:
        func_080C9574(0x45, 0);
        func_0804C834(data_03000E30.entries, 0x40);
        func_08141748(3);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_080038E8(2);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 25:
        func_0804C834(data_03000E30.entries, 0x40);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        data_0200F38C = func_080070C8(g_state_0200F390, 0x2320);
        /* The work buffer and its size, set as src/080245DC.c sets them. */
        {
            void **buffer = &data_03002778;
            u32 size = 0x22E0;

            *buffer = func_08007138(data_0200F38C, size);
            func_08137B20(*buffer, 1);
            data_03000E54 = size;
        }
        func_080038C8(6);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 26:
        func_0804C834(data_03000E30.entries, 0x40);
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        data_0200F38C = func_080070C8(g_state_0200F390, 0x2320);
        /* The work buffer and its size, set as src/080245DC.c sets them. */
        {
            void **buffer = &data_03002778;
            u32 size = 0x22E0;

            *buffer = func_08007138(data_0200F38C, size);
            func_08137B20(*buffer, 1);
            data_03000E54 = size;
        }
        func_080038C8(7);
        g_state_03002810->phase = 0xFD;
        *state = 0xFD;
        break;
    case 11:
        func_080069F4(&data_03002720, 5);
        *state = g_state_03002810->phase;
        break;
    case 13:
        if (--g_state_03002810->timer == 0) {
            *state = data_0200F388;
            data_0200F388 = data_0200F389;
        } else {
            func_0804BDDC(8, g_state_03002810->timer);
        }
        break;
    case 14:
        if (++g_state_03002810->timer == 8) {
            *state = data_0200F388;
            data_0200F388 = data_0200F389;
        } else {
            func_0804BDDC(8, g_state_03002810->timer);
        }
        break;
    case 0xFE:
        func_080316D0();
        func_08006B5C(&data_03002720);
        func_08031264();
        func_0800718C(data_0200F38C);
        break;
    }
}
