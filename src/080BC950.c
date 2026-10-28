#include "ffta.h"

typedef struct Unit080BC950 Unit080BC950;

typedef struct State080BC950 {
    void *context;
    Unit080BC950 *unit;
    u8 unknown_08[0x1C0];
} State080BC950;

typedef void (*BufferInitializer080BC950)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern Unit080BC950 *func_08099544(void *context);
extern BufferInitializer080BC950 const g_callbacks_0836D4B8[];

/* Complete [0x080BC950, 0x080BC984): 52 bytes, 20 instructions. */
State080BC950 *func_080BC950(void *context)
{
    u32 size = sizeof(State080BC950);
    State080BC950 *state = func_08022840(size);

    g_callbacks_0836D4B8[0](state, size);
    state->unit = func_08099544(context);
    state->context = context;
    return state;
}
