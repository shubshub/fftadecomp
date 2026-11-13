#include "ffta.h"

// Complete [0x0806E848, 0x0806E960): 280 bytes.
// Target bytes:
// f0b557464e464546e0b486b081468846039204930e9e0f980906090e88463604
// 360c0006000e0590310609164846a9f777f90004000c4a46917d0131d4f064f8
// 4a46517d051c4d436d00908b2d182d042d0c2e486a010469a4184900201ca5f7
// eff82b4f38682b498a465044211c803101220092039a0023a6f726fc38685044
// 4a46517d05398901641800218a460091211c049a0523baf75dff4a46537d3604
// f6131c1c74432404240c4046800480468721490488444246120c904602200090
// 05980190514602914846211cbcf726f902342404240c04352d042d0c4a46537d
// 981e0006000e009050460190012102914846211c2a1cbcf711f906b038bc9846
// a146aa46f0bc01bc00470000b008000328f40002f4390000

typedef struct {
    u8 unknown_00[0x0C];
    void *unknown_0C;
    u8 unknown_10[5];
    u8 width;
    u8 count;
    u8 unknown_17[5];
    u16 first_tile;
} Panel0806E848;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState0806E848;

typedef struct {
    u8 unknown_00[0x39F4];
    u8 text[1];
} Root0806E848;

extern TileState0806E848 data_030008B0;
extern Root0806E848 *data_0200F428;
extern u16 func_08017B68(Panel0806E848 *panel, s8 row);
extern void func_08013A88(void *destination, u32 rows);
extern void func_08015110(void *context, void *tiles, const void *text,
                          u32 mode, u32 spacing);
extern void func_0802979C(void *context, void *tiles, u32 number,
                          u32 digits, u32 style);
extern void func_0802AB64(Panel0806E848 *panel, u16 index, u16 value,
                          u8 count, u8 offset, u16 tag, u8 flag);

void func_0806E848(Panel0806E848 *panel, u8 slot, const void *text,
                   u32 number, u16 row, u8 tag)
{
    u16 value = func_08017B68(panel, row) % (panel->count + 1)
              * panel->width * 2 + panel->first_tile;
    u8 *tiles = data_030008B0.tiles + value * 32;
    u16 index;

    func_08013A88(tiles, panel->width * 2);
    func_08015110(data_0200F428->text, tiles + 0x80, text, 0, 1);
    func_0802979C(data_0200F428->text, tiles + (panel->width - 5) * 64,
                  number, 5, 0);
    index = panel->width * ((s16)row << 1);
    func_0802AB64(panel, index, slot * 4 + 0x10E, panel->width, 2, tag, 0);
    index += 2;
    value += 4;
    func_0802AB64(panel, index, value, panel->width, panel->width - 2, 0, 1);
}
