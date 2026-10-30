#include "ffta.h"

/* Complete [0x0806E528, 0x0806E59C): 116 bytes, 45 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[3];
    u8 x;
    u8 y;
    u8 width;
    u8 columns;
    u8 unknown_17[7];
    u8 stride;
} Window0806E528;

typedef struct {
    u8 unknown_00[0x1494];
    u16 *tiles;
    u8 unknown_1498[0x28];
    Window0806E528 window;
    u8 unknown_14e0[0x5a8];
    u8 mode;
    u8 unknown_1a89[0x25f];
    u16 extra_tiles[0];
} State0806E528;

extern State0806E528 *data_0200F428;
extern void func_0806E59C(void);
extern u8 func_0806FE14(const u8 *);
extern void func_0802B108(Window0806E528 *);
extern void func_08070070(Window0806E528 *, u16 *, u8, u8, u8, u8);

void func_0806E528(void)
{
    Window0806E528 *window = &data_0200F428->window;

    func_0806E59C();
    if (func_0806FE14(&data_0200F428->mode) == 4) {
        func_0802B108(window);
    } else {
        func_08070070(window, data_0200F428->tiles, 0, 0, 14, 8);
        func_08070070(window, data_0200F428->extra_tiles, 14, 0, 10, 8);
    }
}
