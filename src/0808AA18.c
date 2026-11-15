#include "ffta.h"

typedef struct {
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
} Rect0808AA18;

typedef struct {
    u8 unknown_00[0x10];
    const u16 *first_tiles;
    const u16 *second_tiles;
    u8 unknown_18[8];
    u16 *first_buffer;
    u16 *second_buffer;
    u8 unknown_28[8];
    Rect0808AA18 current;
    u8 unknown_34[0x10];
    Rect0808AA18 saved;
    u8 unknown_48[4];
} Tilemap0808AA18;

extern Tilemap0808AA18 data_030009E0[];
extern void func_0814186C(const void *source, void *destination, u32 control);

/* func_0814186C is the BIOS CpuSet call (`swi 0x0B; bx lr`).  A 16-bit copy
 * in the CpuCopy16 shape: it takes a size in bytes and halves it into the
 * halfword count of the control word, as the fill16 helper of
 * src/080817F8.c does for fills.  The size is signed: the ROM masks the
 * width itself against a 0x001FFFFF literal (0x0808AA96), which an unsigned
 * size does not produce. */
static inline void CopyRow0808AA18(const u16 *source, u16 *destination, s32 size)
{
    func_0814186C(source, destination, (size / 2) & 0x1FFFFF);
}

/* 0x0808AA18..0x0808AAF0: 216 bytes, 101 instructions. */
void func_0808AA18(u32 index)
{
    if (data_030009E0[index].first_buffer) {
        s32 x = data_030009E0[index].current.left;
        s32 y = data_030009E0[index].current.top;
        s32 offset = x + y * 32;
        const u16 *first_source = data_030009E0[index].first_tiles + offset;
        const u16 *second_source = data_030009E0[index].second_tiles + offset;
        u16 *first_destination = data_030009E0[index].first_buffer;
        u16 *second_destination = data_030009E0[index].second_buffer;
        s32 width = data_030009E0[index].current.right - x;
        s32 height = data_030009E0[index].current.bottom - y;

        while (height != 0) {
            CopyRow0808AA18(first_source, first_destination, width * 2);
            first_source += 32;
            first_destination += width;
            CopyRow0808AA18(second_source, second_destination, width * 2);
            second_source += 32;
            second_destination += width;
            height--;
        }
        data_030009E0[index].saved = data_030009E0[index].current;
    }
}
