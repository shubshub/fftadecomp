#include "ffta.h"

/* 0x0804D7E8..0x0804D814: 44 bytes. */
typedef struct {
    u8 first;
    u8 second;
    u16 count;
} SelectionState;

extern SelectionState *func_0804E9D0(void);
extern void *func_0804CA58(u32 bytes);
extern void func_080CB24C(void **objects);
extern void func_0804CA6C(void *buffer);
extern void func_0804E358(u8 category);

void func_0804D7E8(void)
{
    SelectionState *state = func_0804E9D0();
    void **objects;

    state->first = 0;
    state->second = 0;
    state->count = 0;
    objects = func_0804CA58(100);
    func_080CB24C(objects);
    func_0804CA6C(objects);
    func_0804E358(4);
}
