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

typedef struct {
    u8 unknown_00[0x14];
    BufferState window;
} Context08018A0C;

extern Context08018A0C *data_02009190;
extern u8 func_080172F0(BufferState *state);

/* 0x08018A0C - 24 bytes.
 * Target: 00b5044800681430fef76cfc0006000e02bc084790910002
 */
u8 func_08018A0C(void)
{
    return func_080172F0(&data_02009190->window);
}
