#include "ffta.h"

typedef void (*Callback0807DDB8)(void *, u8 *);

typedef struct {
    u8 unknown_00[0xc];
    u8 *states;
} Callbacks0807DDB8;

typedef struct {
    u8 unknown_00[6];
    u8 id;
    u8 unknown_07;
    u8 entity;
    u8 unknown_09[0x2d];
    u8 override_36;
    u8 unknown_37[3];
    u8 override_3a;
    u8 override_3b;
    u8 override_3c;
} Record0807DDB8;

typedef struct {
    u8 unknown_00[0x104];
} Object0807DDB8;

typedef struct {
    u8 unknown_0000[0x42b];
    u8 unknown_042b;
    u8 unknown_042c[0x30];
    Object0807DDB8 object;
    u8 unknown_0560;
    u8 initial_choice;
    u8 unknown_0562[0x6bd];
    u8 choice;
    u8 unknown_0c20[0x511];
    u8 mode;            /* src/0807E2C4.c calls this byte `enabled` */
    u8 unknown_1132;
    u8 flag;
    u8 unknown_1134[0xbd0];
    u8 unknown_1d04;
    u8 unknown_1d05;
    u8 unknown_1d06;
    u8 unknown_1d07[5];
    Record0807DDB8 *record;
    u8 unknown_1d10[0xfaa];
    u8 phase;
    u8 unknown_2cbb[3];
    u8 unknown_2cbe;
    u8 unknown_2cbf[7];
    u16 result;
    u16 value;
    u8 unknown_2cca[0x86];
    void *context;
} State0807DDB8;

/* `x` is read with ldrsb (0x0807E168, 0x0807E192), so it is signed here;
 * src/0807DC24.c only stores to it. */
typedef struct {
    u8 state;
    u8 unknown_01[0x33];
    s8 x;
    u8 unknown_35[0x17];
} Entry0807DDB8;

typedef struct {
    u16 held;
    u16 pressed;
} Input0807DDB8;

extern State0807DDB8 *data_03002818;
extern Callbacks0807DDB8 data_03002730;
extern Entry0807DDB8 data_030009E0[];
extern Input0807DDB8 data_03000000;
extern u8 data_0200F237;
extern u8 data_0200F238;
extern u8 data_0200F239;

/* The compiler calls memcpy (0x081443FC) at 0x0807DDC4 to copy the
 * initialiser of `modes` from .rodata (0x081499C0). */
extern void *memcpy(void *, const void *, unsigned long);
extern void func_0807DC24(int mode);
/* The address of data_0200F239 is loaded at 0x0807DE58, ahead of the
 * arguments and the call at 0x0807DE74: the result is narrowed by the
 * assignment, so the function does not return a u8. */
extern int func_0807D96C(u8, u8, void *);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B858(int index, u16 *destination, u16 tile, u16 count);
extern void func_0808136C(u32 slot, void *resource, u32 renderer,
    u32 column, u32 row, u8 mode);
extern void func_0807B858(void);
extern void func_0808A604(u32 object, u32 command);
extern void func_08089CE4(Object0807DDB8 *object);
/* The result is compared at 0x0807DF70 with no narrowing after the call
 * at 0x0807DF6C, so this caller did not see the u8 return type of
 * src/08084DA0.c. */
extern int func_08084DA0(u32 index, u16 mask);
extern void func_08141540(u32 sound);
extern u8 func_080C9078(const void *data);
extern void func_08088F5C(Object0807DDB8 *object);
extern void func_0807C7E8(void *, u8 *);
extern void func_0807D240(void *, u8 *);
extern void func_08006AF8(Callbacks0807DDB8 *, u8, Callback0807DDB8, u8);
extern void func_08074CE8(u32 width);
extern void func_08074A54(Record0807DDB8 *record);
extern void func_080774B4(Object0807DDB8 *object, int alternate);

/* Complete [0x0807DDB8, 0x0807E2C4): 1292 bytes, including the 19-word
 * jump table at 0x0807DDE4 and the literal pools.  The initialiser of
 * `modes` is the four bytes 01 02 03 05 at 0x081499C0. */
void func_0807DDB8(void *unused, u8 *state)
{
    u8 modes[4] = { 1, 2, 3, 5 };
    int row;

    switch (*state) {
    case 0:
        data_03002818->choice = data_03002818->initial_choice;
        func_0807DC24(0);
        data_03002818->flag = 0;
        data_03002818->unknown_2cbe = 0;
        data_0200F239 = func_0807D96C(modes[data_03002818->choice],
            data_03002818->record->id, data_03002818->context);
        for (row = 0; row < 5; row++)
            func_0808B858(5, func_0808B8E4(5, 1, 0, 2 + row * 2), 0, 14);
        func_0808136C(0, data_03002818->context, 5, 0, 0, 0);
        func_0807B858();
        data_03002818->unknown_1d06 = 3;
        data_03002818->unknown_042b = 10;
        data_0200F238 = 3;
        func_0808A604(3, 5);
        data_0200F237 = 7;
        *state = 9;
        break;
    case 4:
        func_0807DC24(1);
        func_08089CE4(&data_03002818->object);
        for (row = 0; row < 5; row++)
            func_0808B858(5, func_0808B8E4(5, 1, 0, 2 + row * 2), 0, 14);
        data_03002818->phase = 1;
        *state = 7;
        break;
    case 7:
        if (func_08084DA0(0, 0xc7) == 0xff) {
            data_03002818->phase = 8;
            data_0200F238 = 5;
            func_0808A604(5, 5);
            data_0200F237 = 18;
            *state = 9;
        } else if (data_03002818->result == 1) {
            func_08141540(0x9b);
            if (data_03002818->choice == 0) {
                data_03002818->record->override_36 = data_03002818->value;
                data_03002818->record->entity =
                    func_080C9078(data_03002818->record);
            } else if (data_03002818->choice == 1) {
                data_03002818->record->override_3a = data_03002818->value;
            } else if (data_03002818->choice == 2) {
                data_03002818->record->override_3b = data_03002818->value;
            } else if (data_03002818->choice == 3) {
                data_03002818->record->override_3c = data_03002818->value;
            }
            data_0200F238 = 5;
            func_0808A604(5, 5);
            data_0200F237 = 18;
            *state = 9;
        } else if (data_03002818->result == 2) {
            func_08141540(0x68);
            data_03002818->unknown_1d06 = 0;
            data_0200F238 = 5;
            func_0808A604(5, 5);
            data_0200F237 = 18;
            *state = 9;
        } else {
            if (data_03000000.pressed & 0x100) {
                func_08141540(0x64);
                data_03002818->unknown_1d06 = 0;
                if (data_03002818->choice == 0)
                    data_03002818->mode = 1;
                else if (data_03002818->choice == 1)
                    data_03002818->mode = 2;
                else if (data_03002818->choice == 2)
                    data_03002818->mode = 3;
                else
                    data_03002818->mode = 5;
                func_08088F5C(&data_03002818->object);
                data_0200F237 = 8;
                *state = 11;
            }
            if (data_03002818->phase == 6)
                func_0808A604(5, 2);
        }
        break;
    case 11:
        if (data_030009E0[4].x > 29) {
            func_0808A604(5, 5);
            data_030009E0[4].x = 30;
            *state = data_0200F237;
        } else {
            data_030009E0[4].x++;
        }
        func_0808A604(4, 3);
        break;
    case 10:
        if (data_030009E0[4].x <= 20) {
            data_03002818->unknown_1d06 = 3;
            data_030009E0[4].x = 20;
            *state = data_0200F237;
        } else {
            data_030009E0[4].x--;
        }
        func_0808A604(4, 3);
        break;
    case 8:
        if (data_03002818->mode == 1) {
            /* Stores the value just tested: strb r1, [r0] at 0x0807E1DC. */
            data_03002818->mode = 1;
            func_08006AF8(&data_03002730, 7, func_0807C7E8, 2);
        } else {
            func_08006AF8(&data_03002730, 7, func_0807D240, 2);
        }
        *state = 16;
        break;
    case 16:
        if (data_03002730.states[7] == 18) {
            data_03002818->unknown_1d04 = 0;
            func_08074CE8(30);
            func_08074A54(data_03002818->record);
            func_080774B4(&data_03002818->object, 1);
            data_030009E0[4].x = 30;
            if (data_0200F239 == 0)
                func_0807DC24(2);
            data_0200F237 = 4;
            *state = 10;
        }
        break;
    case 9:
        if (data_030009E0[data_0200F238].state == 0)
            *state = data_0200F237;
        break;
    case 17:
        func_0808A604(5, 5);
        *state = 18;
        break;
    case 18:
        /* An empty case: the bound at 0x0807DDCA is 18 and the table has
         * nineteen words, the last one the common exit 0x0807E2BC. */
        break;
    }
}
