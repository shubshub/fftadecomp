#include "ffta.h"

typedef struct {
    u16 column;
    u8 unknown_02[2];
    u16 row;
    u8 unknown_06[2];
} Cell08024A24;

typedef struct {
    void *object;
    u8 mode;
    u8 unknown_05[7];
    Cell08024A24 cell;
    Cell08024A24 previous;
} State08024A24;

extern u8 func_0801BDB0(void);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801C918(s16 first, s16 height, s16 second,
                         s16 *x, s16 *y, s16 *depth);
extern void func_0801C960(s16 x, s16 y, s16 *first, s16 *second);
extern u16 func_0801B938(s16 x, s16 y);
extern void func_08025238(State08024A24 *state);

/* 0x08024A24..0x08024ABA: 150 bytes, no literal pool.
 * 70b584b0061cf7f7c1f9000600283ed1b0894101103102aa1180318a4a01103203ad
 * 2a800006000e0906090ef8f7e2f80006000d6c460a34208002a80021405e0022a15e
 * 0023ea5e0094019502abf7f751ff02a80021405e0022a15e02aa231cf7f76cff02a8
 * 00887838000400142188603909040914f6f74dfff06831697061b1613079042802d1
 * 301c00f0c3fb04b070bc01bc0047
 */
void func_08024A24(State08024A24 *state)
{
    s16 x;
    s16 y;
    s16 depth;

    if (func_0801BDB0() == 0) {
        x = (state->cell.column << 5) + 16;
        depth = (state->cell.row << 5) + 16;
        y = func_0801CC18(state->cell.column, state->cell.row) << 4;
        func_0801C918(x, y, depth, &x, &y, &depth);
        func_0801C960(x, y, &x, &y);
        func_0801B938(x - 120, y - 96);
        state->previous = state->cell;
        if (state->mode == 4)
            func_08025238(state);
    }
}
