#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[4];
} Position;

typedef struct {
    u8 unknown_00[0x80];
    Position positions[2];
} DisplayState;

extern const u8 data_08391544[];
extern const u8 data_08391530[];
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);

/* 080292E0..08029350: 112 bytes, 50 instructions. */
void func_080292E0(const DisplayState *state)
{
    s32 index;

    for (index = 0; index < 2; index++) {
        func_08001F34(data_08391544, state->positions[index].x + 8, state->positions[index].y,
                     0, 0, 0, 0, 0, index ? 0x10 : 0, 0, 0);
        func_08001F34(data_08391530, state->positions[index].x, state->positions[index].y,
                     0, 0, 0, 0, 0, 0, 0, 0);
    }
}
