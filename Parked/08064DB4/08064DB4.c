#include "ffta.h"

typedef struct SelectionIndexView {
    u8 unknown_00[0x3C28];
    u16 index;
} SelectionIndexView;

extern u8 g_state_02000000[];

u32 func_080CE4DC(u16 index, u8 selector);
u8 func_080CB320(u16 identifier);
u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
s32 func_080CA900(u16 identifier, u8 quantity);

u32 func_08064DB4(void)
{
    const SelectionIndexView *state = (const SelectionIndexView *)g_state_02000000;
    u32 category = func_080CE4DC(state->index, 0x12);
    u16 identifier;
    u16 counter;

    if (category == 1) {
        identifier = 0x94;
        counter = 2;
    } else if (category == 0) {
        identifier = 0x33;
        counter = 1;
    } else {
        identifier = 0x11E;
        counter = 4;
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
