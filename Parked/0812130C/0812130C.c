#include "ffta.h"
#include "control_flags.h"
#include "effect_registry.h"

/* Complete [0x0812130C, 0x08121906): 1530 bytes, including the literal
 * pools and the 22-word jump table at 0x081213EC.  A script player: each
 * step runs record data_083A7A34[step] (16 bytes, 75 records). */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *group;
    void *unknown_08;
} Request0812130C;

typedef struct {
    u16 step;
    u16 delay;
    u8 unknown_04[4];
    u16 id;
    u8 unknown_0A[2];
    void *script;
    void *unknown_10;
    void *unknown_14;
    void *group;
    u8 count;
    u8 unknown_1D[3];
    void *objects[4];
} State0812130C;

typedef struct {
    u8 op;
    u8 unknown_01;
    u16 id;
    u8 delay;
    u8 unknown_05[3];
    u32 first;
    u32 second;
} Step0812130C;

typedef struct {
    u8 unknown_00[0x34];
    u16 unknown_34;
} Object0812130C;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;
extern u16 data_03003860;
extern const Step0812130C data_083A7A34[];

extern u8 func_080DD494(void *group);
extern void *func_080DD4B4(void *group, u8 index);
extern Object0812130C *func_080DD350(void *object);
extern void *func_080D3818(u16 id, void *first, void *second);
extern void *func_080D3888(void *script);
extern u8 func_080D8B4C(void);
extern void func_0801E6F0(s16 *x, s16 *y);
extern int func_080D8B28(s16 x, s16 y);
extern void func_080DBED4(u8 selector, u8 flag, void *skip, void *arg);
extern void func_080D3AC0(u8 enabled);
extern void func_080D4020(void);
extern void func_0801B878(void);
extern void func_080DE390(void *object);
extern void func_080DBEB4(void *object, u8 visible);
extern void func_080DE10C(void *object, u16 command);
extern s8 func_080DBC88(void *object);
extern void func_080DBC90(void *object, s8 value);
extern u8 func_080DBC18(void *object, u32 value);
extern void func_080DBD70(void *object, s16 x, s16 y, s16 z);
extern void func_0801AD60(u8 mode);
extern void func_0801DB78(void);
extern u16 func_080035A8(u8 index);
extern void func_0801AE20(void);
extern u8 func_0801AE10(void);
extern void func_0801DB3C(void);

/* The objects a record's target byte selects.  The ROM has this block three
 * times (0x0812152E, 0x08121588, 0x081215E6): the word at +0xC is read as a
 * byte (ldrb at 0x08121536) and count is loaded before the tests (0x08121538),
 * and each caller's first/end pair lives in the frame (sp+4/5, sp+6/7,
 * sp+8/9) with no call taking its address.  Targets 1 and 2 keep their tests
 * (cmp #1 at 0x08121546, cmp #2 at 0x0812154A). */
static inline void select_range(u8 target, u8 count, u8 *first, u8 *end)
{
    u8 start;

    if (target == 1)
        start = 0;
    else if (target == 2)
        start = 0;
    else if (target == 3)
        start = 1;
    else
        start = 0;
    *first = start;
    *end = start + count;
}

u32 func_0812130C(void *context, Request0812130C *request, State0812130C *state)
{
    u8 i;
    u8 op;
    u32 first;
    u32 second;
    u8 advance;
    u8 finish;

    switch (request->phase) {
    case 0:
        state->unknown_10 = request->group;
        state->unknown_14 = request->unknown_08;
        state->group = request->group;
        state->delay = 1;
        state->count = func_080DD494(state->group);
        for (i = 0; i < state->count; i++)
            state->objects[i] = func_080DD350(func_080DD4B4(state->group, i));
        break;
    case 0x100:
        advance = 1;
        finish = 0;
        if (state->delay != 0 && --state->delay != 0)
            break;
        state->id = data_083A7A34[state->step].id;
        op = data_083A7A34[state->step].op;
        first = data_083A7A34[state->step].first;
        second = data_083A7A34[state->step].second;
        switch (op) {
        case 0:
            if (data_083A7A34[state->step].second == 1) {
                first = (u32)state->objects[0];
            } else if (data_083A7A34[state->step].second == 2) {
                first = (u32)state->objects[0];
                second = (u32)state->objects[1];
            } else if (data_083A7A34[state->step].second == 3) {
                first = (u32)state->objects;
                second = state->count;
            }
            state->script = func_080D3818(state->id, (void *)first, (void *)second);
            break;
        case 1:
            state->script = func_080D3508(state->id, state->group, data_083A7A34[state->step].second);
            break;
        case 2: {
            s16 x, y;

            x = first;
            y = second;
            if (state->id == 1) {
                func_0801E6F0(&x, &y);
                x += first;
                y += second;
            }
            func_080D8B28(x, y);
            break;
        }
        case 3:
            func_080DBED4(data_083A7A34[state->step].id, 1, (void *)first, (void *)second);
            break;
        case 4:
            if (!(data_03000000.pressed & first))
                advance = 0;
            break;
        case 5:
            if (data_03000000.pressed == 0)
                advance = 0;
            if (data_03000000.pressed & first) {
                advance = 0;
                state->step += second;
            }
            break;
        case 6:
            func_080D3AC0(1);
            func_080D4020();
            break;
        case 7:
            func_0801B878();
            break;
        case 8:
            advance = 0;
            state->step += second;
            break;
        case 9: {
            u8 index, end;

            select_range(data_083A7A34[state->step].second, state->count, &index, &end);
            for (; index < end; index++)
                func_080DE390(state->objects[index]);
            break;
        }
        case 10: {
            u8 index, end;

            select_range(data_083A7A34[state->step].second, state->count, &index, &end);
            for (; index < end; index++)
                func_080DBEB4(state->objects[index], 0);
            break;
        }
        case 11: {
            u8 index, end;

            select_range(data_083A7A34[state->step].second, state->count, &index, &end);
            for (; index < end; index++)
                func_080DE10C(state->objects[index], data_083A7A34[state->step].first);
            break;
        }
        case 13: {
            s16 x, y, z;
            s8 direction;

            func_080DD350(state->objects[1])->unknown_34 = 0x76;
            /* objects[1] is loaded after this call (0x08121662). */
            direction = func_080DBC88(state->objects[0]);
            func_080DBC90(state->objects[1], direction);
            func_080DBC18(state->objects[1], 0);
            func_080DBD5C(state->objects[0], &x, &y, &z);
            func_080DBD70(state->objects[1], x, y, z);
            func_080DBEB4(state->objects[1], 0);
            break;
        }
        case 14: {
            Object0812130C *object;
            s16 x, y, z;

            object = func_080DD350(state->objects[0]);
            object->unknown_34 = 0x2D;
            object = func_080DD350(state->objects[1]);
            object->unknown_34 = 0x74;
            func_080DBC90(state->objects[0], 3);
            func_080DBC90(state->objects[1], 3);
            func_080DBC18(state->objects[0], 1);
            func_080DBC18(state->objects[1], 0);
            func_080DE10C(state->objects[0], 0x30);
            func_080DE10C(state->objects[1], 0x2C);
            func_080DBD5C(state->objects[0], &x, &y, &z);
            func_080DBD70(state->objects[0], x, y + 0x40, z);
            func_080DBD70(state->objects[1], x, y + 0x40, z);
            func_080DBEB4(state->objects[0], 0);
            func_080DBEB4(state->objects[1], 0);
            break;
        }
        case 15: {
            Object0812130C *object;

            object = func_080DD350(state->objects[0]);
            object->unknown_34 = 0x4B;
            object = func_080DD350(state->objects[1]);
            object->unknown_34 = 0x49;
            object = func_080DD350(state->objects[2]);
            object->unknown_34 = 0x4A;
            func_080DBC18(state->objects[0], 1);
            func_080DBC18(state->objects[1], 0);
            func_080DBC18(state->objects[2], 0);
            func_080DBC90(state->objects[0], 1);
            func_080DBC90(state->objects[1], 0);
            func_080DBC90(state->objects[2], 3);
            func_080DE10C(state->objects[0], 4);
            func_080DE10C(state->objects[1], 4);
            func_080DE10C(state->objects[2], 4);
            func_080DBD70(state->objects[0], 0xF0, 0xA0, 0xF0);
            func_080DBD70(state->objects[1], 0x130, 0xA0, 0x70);
            func_080DBD70(state->objects[2], 0xD0, 0xA0, 0xF0);
            break;
        }
        case 16:
            func_080DD350(state->objects[0])->unknown_34 = 0x2C;
            func_080DBC18(state->objects[0], 0);
            func_080DBC90(state->objects[0], 0);
            func_080DE10C(state->objects[0], 0x14);
            break;
        case 17:
            func_080DBED4(0, 0, 0, 0);
            func_0801AD60(1);
            func_0801DB78();
            g_control_flags_03000940.display &= ~func_080035A8(0);
            g_control_flags_03000940.display &= ~func_080035A8(1);
            break;
        case 18:
            data_03003860 = 0;
            break;
        case 19:
            func_080DBED4(0, 1, 0, 0);
            func_0801AE20();
            break;
        case 20:
            if (func_0801AE10() == 0) {
                advance = 0;
                break;
            }
            func_0801DB3C();
            func_0801B878();
            g_control_flags_03000940.display |= func_080035A8(0);
            g_control_flags_03000940.display |= func_080035A8(1);
            break;
        case 21:
            finish = 1;
            break;
        }
        if (finish)
            request->phase = 0x102;
        else if (advance)
            request->phase++;
        break;
    case 0x101:
        if (func_080D8B4C())
            break;
        state->script = func_080D3888(state->script);
        if (state->script)
            break;
        state->delay = data_083A7A34[state->step].delay;
        state->step++;
        if (state->step <= 0x4A)
            request->phase = 0x100;
        else
            request->phase++;
        break;
    case 0x102:
        request->phase = 2;
        break;
    }
    return 0;
}
