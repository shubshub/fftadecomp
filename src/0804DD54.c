#include "ffta.h"
#include "control_flags.h"

// func_0804DD54 - [0x0804DD54, 0x0804DDCC): 120 bytes, 47 instructions.
//
// target f0b59620c001fef77dfe041c1649b7f76bfbc021c90496229201201c
//        f3f07cfd201cfef779fe114e114845690021114f08014c1c401a8000
//        8219880141191d231088088002320231013b002bf8da211c1329eddd
//        398880225200101c08433880f0bc01bc0047000070fa3a08643d3b08
//        600e000340090003
//
// Allocates a 0x4B00-byte scratch buffer, has func_0800543C fill it from
// the ROM data at data_083AFA70, copies it to the start of VRAM (count 0x2580
// halfwords) and frees it.  Then it copies a 30x20 halfword tile map from
// data_083B3D64 into the 32-halfword rows of the background map that
// data_03000E60's tile pointer names, and sets the BG0 enable bit in the
// DISPCNT shadow.  The map rows are indexed flat, row * 30 and row * 32.

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} Layer0804DD54;

extern Layer0804DD54 data_03000E60;
extern const u8 data_083AFA70[];
extern const u16 data_083B3D64[];

extern void *func_0804CA58(u32 size);
extern void func_0804CA6C(void *allocation);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_0814186C(const void *source, void *destination, u32 size);

void func_0804DD54(void)
{
    void *buffer = func_0804CA58(0x4B00);
    const u16 *map;
    u16 *tiles;
    s32 row;
    s32 column;

    func_0800543C(buffer, data_083AFA70);
    func_0814186C(buffer, (void *)0x06000000, 0x2580);
    func_0804CA6C(buffer);

    map = data_083B3D64;
    tiles = data_03000E60.tiles;
    for (row = 0; row < 20; row++) {
        for (column = 0; column < 30; column++)
            tiles[row * 32 + column] = map[row * 30 + column];
    }

    g_control_flags_03000940.display |= 0x100;
}
