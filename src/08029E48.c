#include "ffta.h"

/* Complete target [0x08029E48, 0x08029F18): 208 bytes, 89 instructions.
 * f0b54f464646c0b481b0141c0899099a120681460f04f8121b041914401840004d46
 * 69690d18002a10d16e460224002737806846291c044a17f1f4fc4035013c002cf5da
 * 35e000000a000001261c002e00d11b4e002498461a4a311c1088523008800232023101
 * 341d2cf7d90224301c291c0a2217f1d6fc14364035013c002cf5da1148114940180268
 * d0231b02301c0821fff77bfff812213042461114401840004d4669690d18301c291c08
 * 22d7f727f801b018bc9846a146f0bc01bc0047b03c00027c52950800000002641f0000
 */
struct Window08029E48 {
    u8 unknown_00[0x14];
    u16 *tilemap;
};

struct Resources08029E48 {
    u8 unknown_00[0x1F64];
    u32 funds;
};

extern u16 data_02003CB0[];
/* Three rows of ten frame tiles (0xD000..0xD010); the word after it at
 * 0x089552B8 starts other data. */
extern const u16 data_0895527C[30];
extern struct Resources08029E48 g_state_02000000;
extern void func_08029DD4(u16 *dst, u16 count, u32 value, u16 base);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern s32 func_08000F48(const void *source, void *destination, u16 count);

void func_08029E48(void *layer, void *unused, u16 *buffer,
                   s16 x, s16 y, u8 visible)
{
    /* The ROM keeps the layer argument in r0 past the stack-argument loads
     * (y is loaded into r1 at 0x08029E54) and copies it to sb only at
     * 0x08029E5A: a local initialised from the parameter, as in
     * src/08016210.c. */
    struct Window08029E48 *window = layer;
    u16 *destination = window->tilemap + (y * 32 + x);
    u16 *work;
    s32 i;
    s32 row;

    if (visible == 0) {
        for (i = 0; i < 3; i++) {
            /* The zero-fill idiom of src/08029DD4.c and src/08035AD8.c. */
            u16 clear;
            u16 *fill = &clear;

            *fill = 0;
            func_0814186C(fill, destination, 0x0100000A);
            destination += 32;
        }
    } else {
        work = buffer;
        if (work == 0)
            work = data_02003CB0;
        /* One counter serves all three loops (r4 at 0x08029E74, 0x08029E9C
         * and 0x08029EB4); this bound is unsigned (bls at 0x08029EB2),
         * while the row loops compare signed and are reversed (bge). */
        for (i = 0; i < sizeof(data_0895527C) / sizeof(data_0895527C[0]); i++)
            work[i] = data_0895527C[i] + 0x52;
        for (i = 0; i < 3; i++) {
            func_0814186C(work, destination, 10);
            work += 10;
            destination += 32;
        }
        func_08029DD4(work, 8, g_state_02000000.funds, 0xD000);
        row = y * 32 + 0x21;
        destination = window->tilemap + (row + x);
        func_08000F48(work, destination, 8);
    }
}
