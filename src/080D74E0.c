#include "ffta.h"

// Target: complete [0x080D74E0, 0x080D758C), 172 bytes, 75 instructions.
extern const u16 data_08149AC4[];
extern const u16 data_08149ACC[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern u16 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);

void func_080D74E0(u8 layer, u8 first, u8 second, s16 x, s16 y,
                   u32 tiles, u32 map)
{
    u16 first_values[4];
    u16 second_values[4];

    func_081443FC(first_values, data_08149AC4, sizeof(first_values));
    func_081443FC(second_values, data_08149ACC, sizeof(second_values));
    func_080034B8(first_values[first] | func_08003A74(map) |
                  func_08003A80(tiles) | second_values[second], layer);
    func_08003508(x, layer);
    func_08003558(y, layer);
}
