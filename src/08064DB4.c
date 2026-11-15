#include "ffta.h"

typedef struct SelectionIndexView {
    u8 unknown_00[0x3C28];
    u16 index;
} SelectionIndexView;

extern u8 g_state_02000000[];

u32 func_080CE4DC(u16 index, u8 selector);
u8 func_080CB320(u32 identifier);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
s32 func_080CA900(u16 identifier, u8 quantity);

/* Complete [0x08064DB4, 0x08064E2C): 120 bytes, 47 instructions.
 * 30b50748074940180088122169f08cfb012809d001280ad2332401250ae00000000000
 * 02283c00009424022502e08f24640004250b484460201c66f097fa0006002811d0281c
 * 64f0d5fb0006000efe2805d8411c0906090e281c64f0d7fb0e2007e00000d020000220
 * 1c012165f06efd0d2030bc02bc0847
 *
 * The dispatch is a three-node case tree (cmp #1, beq, cmp #1, bhs), so a
 * third case label shares the default body.  Its value is not fixed by the
 * bytes; 2 is the value the sibling func_08064E54 tests on the same field,
 * and func_08064E2C tests 0.
 */
u8 func_08064DB4(void)
{
    const SelectionIndexView *state = (const SelectionIndexView *)g_state_02000000;
    u32 category = func_080CE4DC(state->index, 0x12);
    u16 identifier;
    u16 counter;

    switch (category) {
    case 0:
        identifier = 0x33;
        counter = 1;
        break;
    case 1:
        identifier = 0x94;
        counter = 2;
        break;
    case 2:
    default:
        identifier = 0x11E;
        counter = 4;
        break;
    }

    ((Record *)0x020020D0)->field_04 = identifier;
    if (func_080CB320(identifier)) {
        u8 value = func_080C95A8(counter);

        if (value < 255)
            func_080C95C0(counter, (u8)(value + 1));
        return 14;
    }

    func_080CA900(identifier, 1);
    return 13;
}
