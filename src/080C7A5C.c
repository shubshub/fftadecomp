#include "ffta.h"

/* 0x080C7A5C..0x080C7A74: 24 bytes. */
typedef struct {
    void *handle;
} State;

extern void func_080C7858(State *state);
extern void func_08007170(void *handle, u32 value);

void func_080C7A5C(State *state, u32 value)
{
    func_080C7858(state);
    func_08007170(state->handle, value);
}
