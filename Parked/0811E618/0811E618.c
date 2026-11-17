#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *units;
} Task0811E618;

typedef struct {
    u16 step;
    u8 count;
    u8 unknown_03;
    u8 unknown_04[4];
    void **sources;
    void *units[3];
    void *effects[3];
    void *startup;
    void *flash;
} State0811E618;

typedef struct {
    u8 unknown_00[0x34];
    u16 value;
} Unit0811E618;

extern const u8 data_083A734C[];
extern const u8 data_083A7364[];
extern const u8 data_084FAAA4[];
extern const u8 data_08149FC4[];
extern const u8 data_08149FC7[];
extern const u8 data_08149FCA[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080D7A70(const void *data, u32 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void *func_080DD34C(void *source);
extern Unit0811E618 *func_080DD350(void *unit);
extern void func_080D35D8(void);
extern void func_080DBDC8(void *unit, s16 *x, s16 *y);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                           s16 depth, u8 a6, u8 a7, u8 a8);
extern void func_08011198(void *object);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080DE390(void *unit);
extern u8 func_080D5F24(void **objects, u16 count);

// Complete [0x0811E618, 0x0811E7E0), 456 bytes.
// Target:
// f0b557464e464546e0b489b082468946171c098880204000814230d0814204dc
// 00290dd0012927d0c5e00448814231d00130814200d1b3e0bde0000001010000
// 49464868b8600b4802215246b9f704fa786200253e1c0c36b868ac0020180068
// bef768fe34192060681c0006050e022df2d9a0e04c733a08b4f7a2ff9be0786a
// b9f710fa7862002800d094e04a46108801308fe03c4904a8032225f0a3fe05ad
// 3a49281c032225f09dfe06ac3849201c062225f097fe00208046694641441031
// 38880978884232d141468e00381c0c308019006808ac6d462235211c2a1cbdf7
// 67fb0020225e00216b5e2a4800900620019000200290039027480021b7f7d4fa
// 391c183189190860f2f63afd0120424610400822002800d01022042002435046
// 00901e4801210023c1f724fbb86269464144143138880978884213d141468800
// 3c1c0c3424182068bef7f6fd4246510069441831098881862068bff70dfeb878
// 0130b870404601300006000e80460228a3d9388801303880b87802281bd94946
// 08880130088016e0c49f1408c79f1408ca9f1408b1030000a4aa4f0864733a08
// 381c18300321b7f7b1fb0006002802d002204a461080002009b038bc9846a146
// aa46f0bc02bc0847
u32 func_0811E618(void *parent, Task0811E618 *task, State0811E618 *state)
{
    switch (task->phase) {
    case 0: {
        u8 i;

        state->sources = task->units;
        state->startup = func_080D7A70(data_083A734C, 2, parent);
        for (i = 0; i < 3; i++)
            state->units[i] = func_080DD34C(state->sources[i]);
        break;
    }
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        state->startup = func_080D7ABC(state->startup);
        if (state->startup == 0)
            task->phase++;
        break;
    case 0x101: {
        u8 start[3];
        u8 finish[3];
        u16 values[3];
        s16 x;
        s16 y;
        u32 count;
        u8 i;

        func_081443FC(start, data_08149FC4, 3);
        func_081443FC(finish, data_08149FC7, 3);
        func_081443FC(values, data_08149FCA, 6);
        for (i = 0; i < 3; i++) {
            if (state->step == start[i]) {
                func_080DBDC8(state->units[i], &x, &y);
                state->effects[i] = func_080D5CC0(data_084FAAA4, 0, x, y,
                                                  0x3B1, 6, 0, 0);
                func_08011198(state->effects[i]);
                count = (i & 1) ? 0x10 : 8;
                state->flash = func_080DFD8C(data_083A7364, 1, count | 4, 0,
                                             parent);
            }
            if (state->step == finish[i]) {
                func_080DD350(state->units[i])->value = values[i];
                func_080DE390(state->units[i]);
                state->count++;
            }
        }
        state->step++;
        if (state->count > 2)
            task->phase++;
        break;
    }
    case 0x102:
        if (func_080D5F24(state->effects, 3))
            task->phase = 2;
        break;
    }
    return 0;
}
