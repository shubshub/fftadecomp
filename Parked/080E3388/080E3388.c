#include "ffta.h"

// Target: complete [0x080E3388, 0x080E35CC), 580 bytes.
typedef struct {
    u16 state;
    u8 unknown_02[6];
    void *object;
    u8 unknown_0C[8];
    s16 kind;
} EffectTask;

typedef struct {
    u8 unknown_00[2];
    u8 special;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *object;
    void *startup;
    u8 unknown_10[4];
    void *particle;
    void *script;
    void *loader;
    void *effect;
} EffectState;

extern const u8 data_083960A8[];
extern const void *const data_083960F0[];
extern const u8 data_083960F8[];
extern const u8 data_08396102[];
extern const u8 data_0839610C[];
extern u16 g_control_flags_03000940;

extern void func_080DE268(void *object);
extern void func_080D38B4(void);
extern int func_080DE488(void *object);
extern void *func_080D7A70(const void *data, u32 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void *func_080DC1E8(void *object, u8 first, u8 second, u8 mode,
                           void *source, void *destination, void *parent);
extern void *func_080DBA5C(void *loader);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern u32 func_080035A8(u8 layer);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080DC224(void *object, s16 x, s16 y, s16 *out_x, s16 *out_y);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D6098(s16 x, s16 y, u16 third, u8 mode, u16 count,
                           void *target, const void *data, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 count, u16 option,
                           void *parent);
extern void *func_080D3F08(void *script);
extern void func_080DBEB4(void *object, u8 enabled);
extern void *func_080D6134(void *particle);

u32 func_080E3388(void *parent, EffectTask *task, EffectState *state)
{
    switch (task->state) {
    case 0:
        state->special = 0;
        if (task->kind == 0x165)
            state->special = 1;
        state->object = task->object;
        func_080DE268(state->object);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if ((u8)func_080DE488(state->object)) {
            state->startup = func_080D7A70(data_083960A8, 2, parent);
            task->state++;
        }
        break;
    case 0x101:
        state->startup = func_080D7ABC(state->startup);
        if (state->startup)
            break;
        state->loader = func_080DC1E8(state->object, 0, 0, 6,
                                      (void *)0x0600F9E0, (void *)0x06005000,
                                      parent);
        task->state++;
        break;
    case 0x102:
        state->loader = func_080DBA5C(state->loader);
        if (state->loader)
            break;
        {
            s16 x;
            s16 y;
            u16 setting = func_08003A74(0x06005000) | func_08003A80(0x06008000);

            func_080034B8(setting, 3);
            {
                u32 mask = func_080035A8(3);
                u16 flags = g_control_flags_03000940;

                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            func_080DBDC8(state->object, &state->x, &state->y);
            func_080DC224(state->object, state->x, state->y, &x, &y);
            func_08003508(x, 3);
            func_08003558(y, 3);
        }
        state->script = func_080D3E9C(data_083960F8, parent);
        if (state->special == 1)
            state->particle = func_080D6098(state->x, state->y, 0, 1, 1,
                                            state->unknown_10,
                                            data_083960F0[state->special],
                                            parent);
        state->effect = func_080DFD8C(data_0839610C, 1, 4, 0, parent);
        task->state++;
        break;
    case 0x103:
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        if (state->special == 0)
            func_080DBEB4(state->object, 0);
        else
            func_080DBEB4(state->object, 1);
        state->script = func_080D3E9C(data_08396102, parent);
        if (state->special == 0)
            state->particle = func_080D6098(state->x, state->y, 0, 1, 1,
                                            state->unknown_10,
                                            data_083960F0[state->special],
                                            parent);
        task->state++;
        break;
    case 0x104:
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        {
            u32 mask = func_080035A8(3);
            u16 flags = g_control_flags_03000940;

            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        task->state = 2;
        break;
    }
    return 0;
}
