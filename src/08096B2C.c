#include "ffta.h"

/* 0x08096B2C..0x08096B8C: 96 bytes / 39 instructions. */
typedef struct {
    void *context;
    u8 unknown_04[0x40];
    void *child;
    u8 unknown_48[0x80];
    u8 active;
    u8 unknown_C9[7];
    u32 flags;
    u8 unknown_D4[8];
    u16 count;
    u8 unknown_DE[0xDA];
} State08096B2C;

typedef void (*BufferInitializer)(void *destination, u32 size);
extern State08096B2C data_0200F4E8;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_0809D428(void);
extern void func_0809A5C0(void *context, u8 enabled);
extern u8 func_080C95A8(u16 index);

State08096B2C *func_08096B2C(void *context)
{
    State08096B2C *state = &data_0200F4E8;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->child = func_0809D428();
    state->context = context;
    state->count = 8;
    state->active = 0;
    func_0809A5C0(context, 1);
    if (func_080C95A8(13))
        state->flags |= 0x800;
    return state;
}
