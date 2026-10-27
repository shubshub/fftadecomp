#include "ffta.h"

typedef struct Unit080BC810 {
    void *object;
} Unit080BC810;

typedef struct State080BC810 {
    u8 unknown_00[0x6E];
    u8 success;
    u8 unknown_6F[0x51];
} State080BC810;

typedef void (*BufferInitializer080BC810)(void *destination, u32 size);

extern void *func_08096D7C(void);
extern Unit080BC810 *func_08099544(void *context);
extern u8 func_0812E4A8(const void *object);
extern void *func_08022840(u32 size);
extern BufferInitializer080BC810 const g_callbacks_0836D4B8[];
extern void func_080BB5C4(void *state, void *configuration, u8 first, u8 second);
extern void func_08022854(void *object);

/* Complete [0x080BC810, 0x080BC878): 104 bytes, 42 instructions. */
u32 func_080BC810(void *configuration, u8 first, u8 second)
{
    Unit080BC810 *unit = func_08099544(func_08096D7C());
    State080BC810 *state;
    u32 result;

    if (unit == 0 || !func_0812E4A8(unit->object))
        return 0;

    state = func_08022840(sizeof(State080BC810));
    g_callbacks_0836D4B8[0](state, sizeof(State080BC810));
    func_080BB5C4(state, configuration, first, second);
    result = state->success != 0;
    func_08022854(state);
    return result;
}
