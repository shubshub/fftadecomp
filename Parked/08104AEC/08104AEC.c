#include "ffta.h"

/* Complete target: [0x08104AEC, 0x08105042), 1366 bytes, 629 instructions,
   including the literal pools; sha1 of the ROM bytes
   2c7f62e2064d95ffada1f9bf4d8955f8efb0d9a4 (baserom.bin offset 0x104AEC). */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    u8 unknown_08[14];
    u16 flags;
} Command08104AEC;

typedef struct {
    u8 flags;
    u8 direction;
    u8 count;
    u8 index;
    u16 delay;
    u8 column;
    u8 row;
    u8 unknown_08[8];
    void *member;
    void *children[5];
    void *setup_task;
    void *value;
    void *effects[4];
    void *controller;
} State08104AEC;

typedef struct {
    u16 phase;
    u8 unknown_02[18];
    u16 index;
    u16 direction;
    u8 unknown_18[4];
} Descriptor08104AEC;

typedef struct {
    s16 x;
    s16 y;
} Point08104AEC;

typedef u32 (*Callback08104AEC)(void *task, void *command, void *state);

extern const u8 data_0839F720[];
extern const u8 data_0839F738[];
extern const u8 data_0839F74C[];
extern const u8 data_0839F754[];

extern u32 func_0810493C(void *task, void *command, void *state);
extern void *func_08005B6C(Callback08104AEC callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080DD47C(void *);
extern s8 func_080DBC88(void *);
extern void func_080DBD78(void *, s16 *, s16 *, s16 *);
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16, s16, s16, s16 *, s16 *, s16 *);
extern void func_0801C918(s16, s16, s16, s16 *, s16 *, s16 *);
extern u16 func_0801BB0C(s16 x, s16 y, u16 duration);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DE268(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080E0570(void **, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern u8 func_080DB838(const void *);
extern u8 func_080D8B4C(void);
extern u8 func_080DBAB8(void **objects, u32 count);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);

u32 func_08104AEC(void *task, Command08104AEC *command, State08104AEC *state)
{
    switch (command->phase) {
    case 0: {
        s16 x, y, z;
        s16 world_x, world_y, world_z;
        Point08104AEC point;
        void *unit;
        u8 mode;
        u8 i;

        state->flags = command->flags;
        state->value = command->value;
        mode = 2;
        if (state->flags != 0)
            mode = 0;
        unit = func_080DD47C(state->value);
        state->direction = func_080DBC88(unit);
        func_080DBD78(unit, &x, &y, &z);
        state->column = x;
        state->row = z;
        if (state->direction == 0 || state->direction == 2) {
            state->direction = 0;
            for (z = 0; z < 16 && !func_0801CC7C(x, z); z++)
                ;
            for (world_z = z; world_z < 16 && (func_0801CD08(x, world_z) & 8);
                 world_z++)
                ;
            y = func_0801CC18(x, world_z);
        } else {
            state->direction = 1;
            for (x = 0; x < 16 && !func_0801CC7C(x, z); x++)
                ;
            for (world_x = x; world_x < 16 && (func_0801CD08(world_x, z) & 8);
                 world_x++)
                ;
            y = func_0801CC18(world_x, z);
        }
        func_0801CA78(x, y, z, &world_x, &world_y, &world_z);
        func_0801C918(world_x, world_y, world_z, &x, &y, &z);
        point.x = x - 0x78;
        point.y = y - 0x60;
        state->setup_task = func_080E03F8(state->value, data_0839F720, mode, 6,
                                          &point, task);
        state->count = func_080DD494(state->value);
        for (i = 0; i < state->count; i++) {
            /* The member is assigned to the leader's variable before it is
               passed on: adds r6, r0, #0 at 0x08104D0C. */
            unit = func_080DD4B4(state->value, i);
            func_080DE268(unit);
        }
        state->delay = 30;
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_task = func_080E05DC(state->setup_task);
        if (state->setup_task != 0)
            break;
        if (!func_080D8858(state->value, 0)) {
            command->phase = 2;
            break;
        }
        if (--state->delay != 0)
            break;
        state->controller = func_080DFD8C(data_0839F74C, 1, 4, 0, task);
        state->delay = 30;
        command->phase++;
        break;
    case 0x101: {
        /* Declared in this block: its 28 bytes sit at sp+0x18, between the
           phase 0 halfwords (sp+0x0C to sp+0x17) and this block's
           (sp+0x34 to sp+0x3F). */
        Descriptor08104AEC descriptor;
        s16 x, y, z;
        s16 world_x, world_y, world_z;
        u8 i;

        if (--state->delay != 0)
            break;
        x = state->column;
        z = state->row;
        if (state->direction == 0) {
            for (z = 15; z >= 0 && !func_0801CC7C(x, z); z--)
                ;
            for (world_z = 15;
                 world_z >= 0 && (func_0801CD08(x, world_z) & 9); world_z--)
                ;
            y = func_0801CC18(x, world_z);
        } else {
            for (x = 15; x >= 0 && !func_0801CC7C(x, z); x--)
                ;
            for (world_x = 15;
                 world_x >= 0 && (func_0801CD08(world_x, z) & 9); world_x--)
                ;
            y = func_0801CC18(world_x, z);
        }
        func_0801CA78(x, y, z, &world_x, &world_y, &world_z);
        func_0801C918(world_x, world_y, world_z, &x, &y, &z);
        x -= 0x78;
        y -= 0x60;
        func_0801BB0C(x, y, 200);
        for (i = 0; i < 5; i++) {
            descriptor.index = i;
            descriptor.direction = state->direction;
            state->children[i] = func_08005B6C(func_0810493C, 0x28,
                                               &descriptor, task);
        }
        state->controller = func_080DFD8C(data_0839F754, 1, 4, 0, task);
        command->phase++;
        break;
    }
    case 0x102:
        if (!func_080E0570(state->children, 5))
            break;
        if (func_080D8B4C())
            break;
        state->delay = 40;
        command->phase++;
        break;
    case 0x103:
        if (--state->delay != 0)
            break;
        state->member = func_080DD4A4(state->value, state->index);
        func_080DB838(func_080DD4C4(state->member));
        command->phase++;
        /* Falls through: the store at 0x08104F94 runs into the 0x104 block
           at 0x08104F96. */
    case 0x104: {
        u8 mode;

        if (func_080D8B4C())
            break;
        func_080DBAB8(state->effects, 4);
        mode = (state->index & 1) ? 4 : 2;
        state->effects[state->index & 3] = func_080DCFE4(state->member,
            data_0839F738, 12 - (state->index & 6), 10, mode | 8, task, 10);
        if (++state->index == state->count) {
            command->phase++;
            break;
        }
        state->delay = 40;
        command->phase = 0x103;
        break;
    }
    case 0x105:
        if (func_080DBAB8(state->effects, 4))
            command->phase = 2;
        break;
    }
    return 0;
}
