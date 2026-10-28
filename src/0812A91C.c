#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2F6];
    s8 selector;
    u8 unknown_2F7[0x310 - 0x2F7];
    s8 index;
    s8 position;
    u8 unknown_312[0x327 - 0x312];
    u8 timer;
} CursorState;

typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
} InputState;

extern InputState data_03000000;
extern const u8 data_083A8320[];
extern const u8 data_0851BA52[];

void func_080023D0(void *input);
void func_08141540(u32 sound);
void func_08001CF0(const void *image, s32 x, s32 y, u32 a3,
                   u32 a4, u32 a5, u32 a6, u32 a7, u32 a8,
                   u32 a9, u32 a10);
void func_0812AAC8(CursorState *state);

/* Complete target: [0x0812A91C, 0x0812AAC8), 428 bytes. */
void func_0812A91C(CursorState *state)
{
    u16 up = data_03000000.pressed & 0x40;
    u16 left;
    u8 x;
    u8 y;

    if (up) {
        func_080023D0(&data_03000000);
        func_08141540(108);
        state->position--;
        if (state->position < 0)
            state->position = 5;
    } else if (data_03000000.pressed & 0x80) {
        func_080023D0(&data_03000000);
        func_08141540(108);
        state->position++;
        if (state->position > 5)
            state->position = 0;
    }

    left = data_03000000.pressed & 0x20;
    if (left) {
        func_080023D0(&data_03000000);
        func_08141540(108);
        state->index--;
        if (state->index < 0)
            state->index = data_083A8320[state->position + state->selector * 6] - 1;
    } else if (data_03000000.pressed & 0x10) {
        func_080023D0(&data_03000000);
        func_08141540(108);
        state->index++;
        if (state->index >= data_083A8320[state->position + state->selector * 6])
            state->index = 0;
    }

    if (state->index >= data_083A8320[state->position + state->selector * 6])
        state->index = data_083A8320[state->position + state->selector * 6] - 1;

    x = (u8)state->index * 16;
    y = (u8)state->position * 16 + 36;
    state->timer += 6;
    func_08001CF0(data_0851BA52, x - ((state->timer & 0x7F) >> 5), y,
                   0, 0, 0, 0, 0, 0, 0, 0);
    func_0812AAC8(state);
}
