#include "ffta.h"

/* Complete [0x0808BE0C, 0x0808BF22): 278 bytes, 133 instructions. */
extern void func_08089248(u32, u16, u16, u8, u8, u8, u8);

void func_0808BE0C(s32 selected, const u16 *entries)
{
    u16 row = 1;
    u16 selected_palette = 0xf000;
    u16 normal_palette = 0x9000;

    ++selected;
    if (entries[0]) {
        func_08089248(5, 0xe6, selected == 1 ? selected_palette : normal_palette, row, 0, 2, 2);
        row += 2;
    }
    if (entries[1]) {
        func_08089248(5, 0xea, selected == 2 ? selected_palette : normal_palette, row, 0, 2, 2);
        row += 2;
    }
    if (entries[2]) {
        func_08089248(5, 0xee, selected == 3 ? selected_palette : normal_palette, row, 0, 2, 2);
        row += 2;
    }
    if (entries[3]) {
        func_08089248(5, 0xf2, selected == 4 ? selected_palette : normal_palette, row, 0, 2, 2);
        row += 2;
    }
    if (entries[4]) {
        func_08089248(5, 0xf6, selected == 5 ? selected_palette : normal_palette, row, 0, 2, 2);
        row += 2;
    }
    if (entries[5])
        func_08089248(5, 0xfa, selected == 6 ? selected_palette : normal_palette, row, 0, 2, 2);
}
