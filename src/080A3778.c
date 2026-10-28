#include "ffta.h"

/* 0x080A3778: 208 bytes. */
typedef struct {
    void *data;
} Object;

typedef struct {
    Object *object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0e[0x1e];
} SelectionEntry;

typedef struct {
    Object *object;
    u8 unknown_04[0x0c];
    u16 x;
    u16 y;
    u8 unknown_14[0x0c];
    SelectionEntry entries[15];
    u8 unknown_2b4[0x0c];
    u8 count;
} SelectionState;

typedef struct {
    u8 unknown_00[0x84];
    u8 selected;
} SelectionGlobals;

extern SelectionGlobals g_state_0200F390;
extern void *data_0200F3F0[2];

void func_0812F2A4(u16 x, u16 y, u8 mode);
u8 func_080C8240(const void *object);
u8 func_0809A740(void *context);
u8 func_0809A77C(void *context);
void func_0812F328(u8 index);
u8 func_08131024(void);

void func_080A3778(SelectionState *state, void *context, u8 mode)
{
    s32 i;

    for (i = 0; i < state->count; i++) {
        if (state->object == state->entries[i].object)
            return;
    }

    func_0812F2A4(state->x, state->y, mode);
    if (func_080C8240(state->object->data))
        g_state_0200F390.selected = func_0809A740(context);
    else
        g_state_0200F390.selected = func_0809A77C(context);

    for (i = 0; i < 3; i++) {
        data_0200F3F0[1] = data_0200F3F0[0] = state->object->data;
        func_0812F328(i);
        if (i != 0 && state->count == 0)
            return;
        if (func_08131024() == 6) {
            state->entries[state->count].object = state->object;
            state->entries[state->count].flags |= 0x40;
            state->count++;
            return;
        }
    }
}
