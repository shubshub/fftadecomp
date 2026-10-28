#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 row;
} RegionPosition;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} TilemapSurface;

extern TilemapSurface data_030008B0;
extern TilemapSurface data_03000990;
extern void func_08016A98(u16 *destination, u8 width, u8 height,
                          u16 value, u16 stride);

/* 0802D014..0802D05C: 72 bytes. */
void func_0802D014(RegionPosition *position)
{
    func_08016A98(data_030008B0.tilemap + position->row * 32, 17, 7, 0, 32);
    func_08016A98(data_03000990.tilemap + position->row * 32, 17, 6, 0, 32);
}
