#include "ffta.h"

typedef struct {
    void *object;
    u8 unknown_04[3];
    u8 variant_flags;
    u8 unknown_08[4];
    u16 column;
    u8 unknown_0E[2];
    u16 row;
} State08025238;

extern void *func_0808F79C(void);
extern void (*data_08394038[])(void *, const void *);
extern void (*data_08394040[])(void *, s32);
extern void (*data_08394054[])(void *, s32);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801C918(s16 first, s16 height, s16 second,
                         s16 *x, s16 *y, s16 *depth);
extern void func_0801C960(s16 x, s16 y, s16 *first, s16 *second);
extern void func_08001DAC(const void *source, s32 x, s32 y, s32 depth,
                         u8 mode, u32 extra);
extern void func_0808EFCC(void *object, s16 first, s16 height, s16 second);

/* 0x08025238..0x08025324: 236 bytes, including six literal words. */
void func_08025238(State08025238 *state)
{
    u16 first;
    u16 second;
    s32 height;
    s16 x;
    s16 y;
    s16 depth;
    const s16 *offsets;

    if (state->object == 0) {
        state->object = func_0808F79C();
        data_08394038[0](state->object, (const void *)0x0839155C);
        data_08394040[0](state->object, -124);
        data_08394054[0](state->object, 1);
    }

    first = (state->column << 5) + 16;
    second = (state->row << 5) + 16;
    height = func_0801CC18(state->column, state->row) << 4;
    func_0801C918((s16)first, height, (s16)second, &x, &y, &depth);
    func_0801C960(x, y, &x, &y);
    offsets = (const s16 *)0x0839141C;
    func_08001DAC((const void *)0x08391554, x - 5,
        y - offsets[state->variant_flags >> 1], 0, 0, 0);
    if (state->object != 0)
        func_0808EFCC(state->object, (s16)first, height, (s16)second);
}
