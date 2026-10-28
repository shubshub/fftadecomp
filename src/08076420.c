#include "ffta.h"

typedef struct {
    u8 unknown_000[0x44d];
    u8 mode;
    u8 unknown_44e[0x50e];
    u8 count;
    u8 unknown_95d[0x5d];
    u8 displayed_indices[1];
} SelectionState08076420;

typedef struct {
    u8 unknown_00[0x14];
    u16 enabled;
    u8 unknown_16[6];
} SelectionSprite08076420;

typedef struct {
    u32 unknown_00;
    SelectionSprite08076420 *entries;
} SelectionRenderer08076420;

extern SelectionState08076420 *data_03002818;
extern SelectionRenderer08076420 data_03000E30;
extern const u8 data_0894EB14[];
extern const u8 data_0894EB94[];

extern u8 func_080C95A8(u32 selector);
extern u16 *func_0808B8E4(u32 window, u32 plane, s32 x, s32 y);
extern void func_08035678(u16 tile, u16 *destination, u32 count, u16 step);
extern void func_08035A68(u16 *destination, u32 digits, u32 value, u16 attributes);
extern void func_0804C4D4(void *entries, u16 index, u16 selector,
                         u8 y, u8 x, u8 mode, u8 delay,
                         const u8 *graphics, const u8 *layout, u16 attributes);

/* Complete target [0x08076420, 0x08076560): 320 bytes, 123 instructions. */
void func_08076420(s32 selected)
{
    s32 index;
    s32 i;

    if (data_03002818->mode == 4)
        return;

    if (func_080C95A8(0x33) != 6)
        index = selected;
    else
        index = data_03002818->displayed_indices[selected];

    func_08035678(0xd0bf, func_0808B8E4(0, 1, 26, 19), 2, 1);
    func_08035A68(func_0808B8E4(0, 1, 28, 19), 2, index + 1, 0xf000);

    index = selected;
    for (i = 0; i < data_03002818->count; i++) {
        if (i != index) {
            *func_0808B8E4(0, 1, i + 2, 19) = 0xd0be;
        } else {
            u16 selector;

            if (data_03002818->count == 1)
                selector = 3;
            else if (i > 0) {
                if (i < data_03002818->count - 1)
                    selector = 0;
                else
                    selector = 2;
            } else
                selector = 1;

            data_03000E30.entries[26].enabled = 1;
            func_0804C4D4(data_03000E30.entries, 26, selector,
                (u8)(i * 8 + 16), 160, 0, 0,
                data_0894EB14, data_0894EB94, 0x1bc);
        }
    }
}
