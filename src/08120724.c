#include "ffta.h"
#include "control_flags.h"

// 08120724: complete 420-byte target [0x08120724, 0x081208C8), including its literal pools.

typedef struct Task Task;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *argument;
    u32 value;
    u32 flags;
    u32 unknown_10;
    s16 selector;
    u16 option;
    u16 resource;
    u16 unknown_1a;
} TaskRequest;

typedef struct {
    u8 unknown_00[8];
    Task *fade;
    Task *first;
    Task *second;
} State;

typedef int (*TaskCallback)(Task *, TaskRequest *, void *);
extern Task *func_08005B6C(TaskCallback callback, u16 size,
                          TaskRequest *request, Task *parent);
extern u16 *func_08005BFC(Task *task);
extern int func_080035A8(int);
extern void func_080D4020(void);
extern void func_080D3AC0(u8 enabled);
extern void func_080D35D8(void);
extern Task *func_080E051C(Task *task);
extern int func_0811EF58(Task *, TaskRequest *, void *);
extern int func_0811F5E0(Task *, TaskRequest *, void *);
extern int func_081204A8(Task *, TaskRequest *, void *);
extern u16 data_03003860[];

static inline u8 IsSet(u16 value)
{
    if (value)
        return 1;
    return 0;
}

int func_08120724(Task *parent, TaskRequest *request, State *state)
{
    TaskRequest fade;
    TaskRequest child;

    switch (request->phase) {
    case 0:
        g_control_flags_03000940.display &= ~func_080035A8(0);
        g_control_flags_03000940.display &= ~func_080035A8(1);
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= ~func_080035A8(3);
        func_080D4020();
        data_03003860[0] = 0;
        func_080D3AC0(0);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        state->fade = func_08005B6C(func_0811EF58, 0x7C, &fade, parent);
        request->phase++;
        break;
    case 0x101:
        if (IsSet(*func_08005BFC(state->fade) &= 1)) {
            *func_08005BFC(state->fade) &= 0x7FFF;
            request->phase++;
        }
        break;
    case 0x102:
        if (state->first == 0 && IsSet(*func_08005BFC(state->fade) &= 2))
            state->first = func_08005B6C(func_0811F5E0, 0x2C, &child, parent);
        state->fade = func_080E051C(state->fade);
        if (state->fade == 0)
            request->phase++;
        break;
    case 0x103:
        if (state->second == 0 && IsSet(*func_08005BFC(state->first) &= 2))
            state->second = func_08005B6C(func_081204A8, 0x44, &child, parent);
        state->first = func_080E051C(state->first);
        if (state->first == 0)
            request->phase++;
        break;
    case 0x104:
        state->second = func_080E051C(state->second);
        if (state->second == 0)
            request->phase++;
        break;
    case 0x105:
        request->phase = 2;
        break;
    }
    return 0;
}
