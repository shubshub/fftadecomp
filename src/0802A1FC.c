#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u32 value_14;
} ResourceState0802A1FC;

extern ResourceState0802A1FC data_030008B0;
extern ResourceState0802A1FC data_03000990;

void func_08017424(void *state, u32 first, u32 second,
                   u8 a, u8 b, u8 c, u8 d, u16 value,
                   u8 flags, u16 width, u16 height, u8 mode);
void func_08016C90(void *state, u8 value);
void func_08017D18(void *state, u8 flags);

void func_0802A1FC(u8 *state, u8 a, u8 b, u8 c,
                   u8 d, u16 value, u8 selection)
{
    u32 first = data_030008B0.value_14;
    u32 second = data_03000990.value_14;

    func_08017424(state, first, second, a, b, c, d, value, 0x20, 5, 1, 12);
    func_08016C90(state, selection);
    func_08017D18(state + 0x4c, 0);
    func_08017D18(state + 0x60, 0);
}
