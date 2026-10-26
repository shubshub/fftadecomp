#include "ffta.h"

/* Complete [0x0807974C, 0x08079838): 236 bytes, 113 instructions. */
extern void func_08089248(u8, u16, u16, u8, u8, u8, u8);

void func_0807974C(s32 selected, const u16 *entries)
{
    u16 row = 5;
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
    if (entries[4])
        func_08089248(5, 0xf6, selected == 5 ? selected_palette : normal_palette, row, 0, 2, 2);
}
