#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
} TileRun;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState;

typedef struct DrawContext DrawContext;

extern TileState data_030008B0;
extern const u8 *const g_table_085567F0[];
extern const u8 data_08391784[];
extern const u8 data_08391787[];
extern const u8 data_083917B8[];
extern const u8 data_083917C1[];
extern void func_08013A88(void *destination, u16 count);
extern void func_08015110(DrawContext *, u8 *, const u8 *, u32, u32);
extern void func_0802979C(DrawContext *, u8 *, u32, s32, s32);
extern u8 func_08058608(u32 value);

/* Complete target: [0x0805843C, 0x08058608), 460 bytes, 193 instructions. */
void func_0805843C(TileRun *run, DrawContext *context, u32 value,
    u8 secondary, u8 compact)
{
    u8 *tiles = data_030008B0.tiles + run->tile * 32;
    u8 digits;

    func_08013A88(tiles, run->count * 4);
    /* Both arms end with the same suffix draw and row advance: the ROM
       keeps one copy, 0x0805851E-0x0805853C, entered from the first arm
       by the branch at 0x080584C4. */
    if (compact == 0) {
        func_08015110(context, tiles, g_table_085567F0[0x1C], 5, 1);
        func_08015110(context, tiles + 14 * 32, data_08391784, 5, 1);
        digits = func_08058608(value);
        func_0802979C(context, tiles + 16 * 32, value, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 16) * 32,
            g_table_085567F0[0x2DC], 5, 1);
        tiles += run->count * 64;
    } else {
        func_08015110(context, tiles, g_table_085567F0[0x1C], 5, 1);
        func_08015110(context, tiles + 6 * 32, data_08391784, 5, 1);
        digits = func_08058608(value);
        func_0802979C(context, tiles + 8 * 32, value, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 8) * 32,
            g_table_085567F0[0x2DC], 5, 1);
        tiles += run->count * 64;
    }

    if (compact == 0) {
        func_08015110(context, tiles, g_table_085567F0[0x1D], 5, 1);
        func_08015110(context, tiles + 14 * 32, data_08391784, 5, 1);
    } else {
        func_08015110(context, tiles, data_08391787, 5, 1);
    }

    if (compact == 0) {
        digits = func_08058608(secondary);
        func_0802979C(context, tiles + 16 * 32, secondary, digits, 5);
        func_08015110(context, tiles + (digits * 2 + 16) * 32,
            data_083917C1, 5, 1);
    } else {
        func_0802979C(context, tiles + 38 * 32, secondary, 2, 5);
        func_08015110(context, tiles + 42 * 32, data_083917B8, 5, 1);
    }
}
