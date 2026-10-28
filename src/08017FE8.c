#include "ffta.h"

typedef struct {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 value;
    u8 extra;
} DrawState08017FE8;

extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);

/* Complete [0x08017FE8, 0x08018026): 62 bytes, 30 instructions. */
void func_08017FE8(const DrawState08017FE8 *state)
{
    func_08001CF0(state->source, state->x + state->offset_x,
                  state->y + state->offset_y, 0, 0, 0, 0, 0,
                  state->value, 0, state->extra);
}
