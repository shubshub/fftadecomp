#include "ffta.h"

typedef struct {
    u16 *first;
    u16 *second;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[2];
    u8 kind;
    u8 unknown_17[5];
    u8 flags;
    u8 unknown_1D[3];
    u16 current_x;
    u16 current_y;
    s16 target_x;
    s16 target_y;
} BufferState;

extern u16 func_080161A0(u8 x, u8 y, u8 kind);
extern void func_08016A98(u16 *buffer, u8 width, u8 height, u16 value,
                          u8 kind);
extern void func_08016A08(u16 *buffer, u8 x, u8 y, u8 kind);

/* 080172F0..08017380: 144 bytes, 67 instructions. */
u8 func_080172F0(BufferState *state)
{
    u16 x, y;
    u16 *destination;
    u8 result;

    if (!(state->flags & 4)) {
        u16 offset = func_080161A0(state->x, state->y, state->kind);

        func_08016A98(state->first + offset, state->width, state->height,
                     0, state->kind);
        func_08016A98(state->second + offset, state->width, state->height,
                     0, state->kind);
    }

    state->current_x = state->target_x;
    state->current_y = state->target_y;
    x = state->current_x;
    y = state->current_y;
    destination = state->second +
                  func_080161A0(state->x, state->y, state->kind);
    func_08016A08(destination, x, y, state->kind);

    result = 0;
    if (x == state->target_x && y == state->target_y)
        result = 1;
    return result;
}
