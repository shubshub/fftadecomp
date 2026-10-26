#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 context[1];
} Root080676F8;

typedef struct {
    u8 unknown_00[0x15];
    u8 row;
} Panel080676F8;

typedef struct {
    Root080676F8 *root;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[0x47];
    Panel080676F8 panel;
    u8 unknown_68[0x30];
    u8 *flags;
} State080676F8;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Tiles080676F8;

extern Tiles080676F8 data_030008B0;
extern u16 func_08017B9C(Panel080676F8 *, s8);
extern u16 func_08017B68(Panel080676F8 *, s8);
extern void func_08013A88(void *, u32);
extern const void *func_0806779C(State080676F8 *, s16);
extern u8 *func_080678C4(State080676F8 *, u8 *, u16);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void func_080675A0(State080676F8 *, void *, u8 *, u16);

/* Complete [0x080676F8, 0x0806779C): 164 bytes, 73 instructions. */
void func_080676F8(State080676F8 *state, s8 row)
{
    Panel080676F8 *panel = &state->panel;
    u32 enabled = 0;
    u8 *tiles;
    u16 index;
    s32 flag;
    const void *text;

    tiles = data_030008B0.tiles + func_08017B9C(panel, row) * 0x20;
    func_08013A88(tiles, panel->row * 2);
    index = func_08017B68(panel, row);
    flag = (s8)state->flags[index];
    if (flag == 0)
        enabled = 1;
    text = func_0806779C(state, (s16)index);
    tiles = func_080678C4(state, tiles, index);
    func_08015110(state->root->context, tiles, text, enabled, 1);
    if (state->mode == 4)
        func_080675A0(state, state->root->context, tiles, index);
}
