#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    s16 row;
    u8 unknown_08[0x320];
    u16 second_source[7][17];
    u8 unknown_416[0x12];
    u16 first_source[6][17];
} TileRows0802CFB0;

typedef struct {
    u8 unknown_00[0x14];
    u8 *map;
} TileMap0802CFB0;

typedef struct Request0802CFB0 Request0802CFB0;

extern TileMap0802CFB0 data_03000990;
extern TileMap0802CFB0 data_030008B0;
extern Request0802CFB0 *func_0802BA08(void);
extern void func_08000BAC(Request0802CFB0 *request, u32 first, u32 second,
                          u16 count, u16 field_10, u16 field_12, u16 field_14);

/* Complete target [0x0802CFB0, 0x0802D014), 100 bytes.
 * f0b583b0041cfef727fd8522d200a118124a0625635f9b015269d21806230093
 * 22260196402502951123d3f7e7fdfef713fdca27bf00e119094a0627e35f9b01
 * 5269d21807230093019602951123d3f7d5fd03b0f0bc01bc0047000090090003
 * b0080003
 */
void func_0802CFB0(TileRows0802CFB0 *state)
{
    func_08000BAC(func_0802BA08(), (u32)state->first_source,
                  (u32)(data_03000990.map + state->row * 64), 17, 6, 34, 64);
    func_08000BAC(func_0802BA08(), (u32)state->second_source,
                  (u32)(data_030008B0.map + state->row * 64), 17, 7, 34, 64);
}
