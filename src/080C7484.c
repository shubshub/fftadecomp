#include "ffta.h"

/* 0x080C7484..0x080C74B4: 48 bytes, 19 instructions, including a pool. */
struct State080C62CC;
struct UnitRecord080C62CC;

extern u8 data_030028A0;
extern void *func_08022840(u32 size);
extern void func_080C62CC(struct State080C62CC *state, struct UnitRecord080C62CC *const *items,
                          s32 count, u8 mode);

struct State080C62CC *func_080C7484(struct UnitRecord080C62CC *const *items, s32 count)
{
    struct State080C62CC *state = func_08022840(0xB4);
    func_080C62CC(state, items, count, (data_030028A0 >> 3) & 1);
    return state;
}
