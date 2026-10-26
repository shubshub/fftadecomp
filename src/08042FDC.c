#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1a];
    u16 selection;
    u8 unknown_1c[0x2c];
} List08042FDC;

typedef struct {
    u8 unknown_00[0x78];
    List08042FDC list;
    u8 unknown_c0[0x0c];
} Record08042FDC;

typedef struct {
    u8 unknown_000[0x954];
    Record08042FDC records[1];
} State08042FDC;

extern State08042FDC *g_state_03002810;
extern u32 func_08017B50(List08042FDC *);
extern void func_08042D4C(s32, s16, List08042FDC *);
extern void func_08037DF0(s32, s16);
extern void func_08042E48(List08042FDC *, u16);

/* 0x08042FDC..0x08043070: 148 bytes, 61 instructions. */
u16 func_08042FDC(s32 index)
{
    State08042FDC *state = g_state_03002810;
    s32 count = (u16)func_08017B50(&state->records[index].list);
    s32 row;

    for (row = 0; row < count; row++) {
        func_08042D4C(index, row, &g_state_03002810->records[index].list);
        func_08037DF0(index, row);
    }
    func_08042E48(&g_state_03002810->records[index].list,
                  (u16)(g_state_03002810->records[index].list.selection * 2));
    return count;
}
