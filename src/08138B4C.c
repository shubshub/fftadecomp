#include "ffta.h"

// Target: complete [0x08138B4C, 0x08138D60), 532 bytes, 211 instructions.

typedef struct {
    u8 unknown_00[0x08];
    const void *first;
    u8 unknown_0c[4];
    const void *second;
} Sources08138B4C;

typedef struct {
    u8 unknown_00[0x1c];
    u16 *tiles;
} Buffers08138B4C;

typedef struct {
    u8 unknown_00[0x0e];
    u16 tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 height;
    u8 unknown_2a[10];
    u8 x;
    u8 y;
    u8 unknown_36[22];
} Window08138B4C;

/* agbcc aligns every struct to 4, and the record sits at entry+0x32 with its
 * u32 text at +0x36; the ROM reads text as two ldrh halves in the compiler's
 * unaligned-access order, which a hand-written (high << 16 | low) does not
 * reproduce.  packed+aligned(2) gives the record its real 2-byte alignment. */
typedef struct __attribute__((packed, aligned(2))) {
    u16 kind;
    u16 unknown_02;
    u32 text;
    u8 unknown_08[0x18];
} Message08138B4C;

typedef struct {
    u8 unknown_00[0x2f];
    u8 alternate;
    u8 unknown_30[2];
    Message08138B4C message;
} Entry08138B4C;

extern Sources08138B4C *data_030027D8;
extern Buffers08138B4C data_03002740;
extern Window08138B4C data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_0600CD20[];
extern const u8 *const g_table_0855A64C[];
extern const u8 *const g_table_08565F14[];

void *func_0808A268(s32 index, u8 kind, const void *first,
    const void *second, u16 *first_tiles, u16 *second_tiles,
    void *third, void *fourth, u8 left, u8 top, u8 width, u8 height,
    u8 x, u8 y, u8 first_width, u8 first_height, u8 second_width,
    u8 second_height);
void func_0814186C(const void *source, void *destination, u32 control);
void func_08016800(void *destination, u8 width, u8 height, u16 flags,
                   u8 stride, u16 tile, u16 palette, u8 mode);
u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
void func_0808B7C0(s32 index, u16 *destination, u16 tile, u16 count,
                   u16 flags);
void func_08015110(void *context, void *destination, const void *text,
                   u32 style, u32 spacing);
void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

void func_08138B4C(Entry08138B4C *entry)
{
    u8 *context = data_02003CB0 + 0x100;
    u8 *buffer = data_02003CB0;
    u16 zero;
    u16 clear;
    u16 tile;

    func_0808A268(7, 12, data_030027D8->first, data_030027D8->second,
                  data_03002740.tiles, data_03002740.tiles + 65, 0, 0,
                  16, 6, 13, 5, 16, 6, 13, 5, 13, 5);
    data_030009E0[7].x = 16;
    data_030009E0[7].y = 6;
    data_030009E0[7].tile = 617;
    zero = 0;
    func_0814186C(&zero, data_0600CD20, 0x01000680);
    func_08016800(data_030009E0[7].first_plane,
                  data_030009E0[7].stride, data_030009E0[7].height,
                  0x800, data_030009E0[7].stride, 13, 3, 11);
    func_0808B7C0(7, func_0808B8E4(7, 1, 1, 2), 617, 13, 0xb000);

    if (entry->message.kind == 1) {
        const u8 *text = entry->alternate
                             ? g_table_08565F14[entry->message.text]
                             : g_table_0855A64C[entry->message.text];

        func_08015110(context, data_0600CD20, text, 5, 1);
    } else if (entry->message.kind == 0) {
        func_08015110(context, data_0600CD20,
                      (const void *)entry->message.text,
                      5, 1);
    } else {
        clear = 0;
        func_0814186C(&clear, buffer, 0x01000020);
        func_0814186C(&entry->message, buffer, 16);
        func_08015110(context, data_0600CD20, buffer, 5, 1);
    }

    if (entry->alternate) {
        tile = 0xd181;
        func_08035678(tile, func_0808B8E4(7, 1, 0, 0), 8, 1);
        tile += 8;
        func_08035678(tile, func_0808B8E4(7, 1, 0, 1), 8, 1);
    } else {
        tile = 0xd191;
        func_08035678(tile, func_0808B8E4(7, 1, 0, 0), 10, 1);
        tile += 10;
        func_08035678(tile, func_0808B8E4(7, 1, 0, 1), 10, 1);
    }
}
