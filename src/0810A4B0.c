#include "ffta.h"

/* 0810A4B0: complete 172-byte owner, including both final literals. */
typedef struct Task10A4B0 Task10A4B0;
typedef struct Object10A4B0 Object10A4B0;

typedef struct Request10A4B0 {
    u16 event;
    u16 unknown_02;
    Object10A4B0 *object;
    u32 index;
    u32 flags;
    u8 unknown_10[4];
    u16 kind;
    u16 argument;
    u8 unknown_18[4];
} Request10A4B0;

typedef struct State10A4B0 {
    u16 current;
    u8 total;
    u8 flag;
    u8 value;
    u8 unknown_05[7];
    Task10A4B0 *child;
    Object10A4B0 *object;
} State10A4B0;

u8 func_080DD494(Object10A4B0 *object);
void func_080D38B4(void);
Task10A4B0 *func_080E051C(Task10A4B0 *task);
u32 func_080EFAB0(Task10A4B0 *task, Request10A4B0 *request, void *state);
Task10A4B0 *func_08005B6C(
    u32 (*callback)(Task10A4B0 *, Request10A4B0 *, void *),
    u16 size, const Request10A4B0 *request, Task10A4B0 *parent);

u32 func_0810A4B0(Task10A4B0 *task, Request10A4B0 *request,
                  State10A4B0 *state)
{
    Request10A4B0 child_request;

    switch (request->event) {
    case 0:
        state->value = request->argument;
        state->object = request->object;
        if (request->flags & 2)
            state->flag = 1;
        state->total = func_080DD494(state->object);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (state->child) {
            state->child = func_080E051C(state->child);
            if (state->child == 0) {
                state->current++;
                if (state->current == state->total)
                    request->event = 2;
            }
        } else {
            child_request.kind = 0x117;
            child_request.argument = 1;
            if (state->current == 0)
                child_request.argument = 0;
            child_request.object = state->object;
            child_request.index = state->current;
            state->child = func_08005B6C(func_080EFAB0, 0x2C,
                                       &child_request, task);
        }
        break;
    }
    return 0;
}
