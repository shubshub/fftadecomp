// Target: complete [0x0810DE24, 0x0810E09C), 632 bytes.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[4];
    u16 command;
    u16 flag;
    u32 unknown_18;
} Request0810DE24;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 unknown_06;
    u8 alternate;
    u8 result;
    u8 unknown_09;
    u16 timer;
    void *handle;
    void *auxiliary;
    void *display;
    void *script;
    void *actor;
    void *loading;
    void *output_task;
    void *effect;
} State0810DE24;

extern const u8 data_083A2950[];
extern const u8 data_083A2974[];
extern const u8 data_083A2978[];
extern const u8 data_083A2980[];
extern const u8 data_088F06B0[];
extern const u8 data_0894DE34[];
extern const u8 data_0894AC40[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern u8 func_080DD494(void *);
extern void *func_080DD47C(void *);
extern u16 func_080DD708(const void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void func_080D8C58(void *, s16 *, s16 *);
extern void func_080D49FC(u8 kind, u8 mode, u16 option, s16 x, s16 y);
extern void *func_080D4B64(u8 kind, const void *data, u16 value, u8 mode);
extern u32 func_080035A8(u8 layer);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags, u16 delay,
                           void *parent);
extern u8 func_080D8924(void *, u8, u16, void *);
extern u32 func_080E7C04(void *, void *, void *);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u32 size,
                           Request0810DE24 *descriptor, void *parent);
extern void *func_080D4D2C(void *display, u8 mode);
extern void *func_080D3F08(void *script);
extern void *func_080D4774(void *auxiliary);
extern void *func_080E051C(void *);

u32 func_0810DE24(void *task, Request0810DE24 *request, State0810DE24 *state)
{
    Request0810DE24 child;
    u8 animation;
    u16 size;
    u8 mode;
    const u8 *table;
    void *owner;

    switch (request->phase) {
    case 0:
        state->flag = request->flag;
        state->actor = request->actor;
        animation = 3;
        if (state->flag != 0)
            animation = 0;
        if (request->flags & 2)
            state->alternate = 1;
        state->loading = func_080E03F8(state->actor, data_083A2950,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->loading = func_080E05DC(state->loading);
        if (state->loading != 0)
            break;
        if (func_080D3B54(state->actor)) {
            request->phase = 2;
            break;
        }
        if (state->flag != 0) {
            state->result = func_080DD494(state->actor);
            request->phase = 0x103;
            break;
        }
        owner = func_080DD47C(state->actor);
        size = 0x54;
        table = data_083A2974;
        mode = 1;
        if (func_080DD708(owner) != 0x44)
            size = 0x34;
        if (state->alternate) {
            size = 0x34;
            table = data_083A2978;
            mode = 2;
        }
        state->output_task = func_080DDF68(state->actor, 0, size, mode,
            &state->ready, table, 0, 0, task);
        request->phase++;
        break;
    case 0x101:
        if (state->ready == 0)
            break;
        func_080D8CD4(state->actor);
        request->phase++;
        break;
    case 0x102:
        if (func_080D8B4C())
            break;
        func_080D8C58(state->actor, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->display = func_080D4B64(0, data_088F06B0, 0x320, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        state->script = func_080D3E9C(data_0894DE34, task);
        state->auxiliary = func_080D4704(data_0894AC40, task);
        state->effect = func_080DFD8C(data_083A2980, 1, 4, 0, task);
        state->result = func_080D8924(state->actor, 0, 0x1E, task);
        if (state->result == 0) {
            request->phase = 0x104;
            break;
        }
        state->timer = 0x26;
        request->phase++;
        break;
    case 0x103:
        state->timer--;
        if (state->timer != 0)
            break;
        child.command = 0x12D;
        child.flag = state->flag;
        child.actor = state->actor;
        child.unknown_08 = 0;
        child.flags = 1;
        state->handle = func_08005B6C(func_080E7C04, 0x14, &child, task);
        request->phase++;
        break;
    case 0x104:
        state->display = func_080D4D2C(state->display, 0);
        if (state->display)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags &= ~mask;
            g_control_flags_03000940.display = flags;
        }
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        state->auxiliary = func_080D4774(state->auxiliary);
        if (state->auxiliary)
            break;
        state->handle = func_080E051C(state->handle);
        if (state->handle == 0)
            request->phase = 2;
        break;
    }
    return 0;
}
