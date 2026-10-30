#include "ffta.h"

typedef struct SearchContext080A215C SearchContext080A215C;

typedef struct {
    u8 unknown_0000[0x3C9E];
    u8 counter_3C9E;
    u8 counter_3C9F;
} State080A215C;

extern State080A215C g_state_02000000;
extern u8 func_080C95A8(u16 index);
extern u8 func_080C8240(void *data);
extern s32 func_0809AA10(SearchContext080A215C *context);

/* 0x080A215C..0x080A21B4:
 * 30 B5 05 1C 0C 1C 0D 20 27 F0 20 FA 00 06 00 28
 * 1B D0 20 68 26 F0 66 F8 00 06 00 28 15 D0 28 1C
 * F8 F7 48 FC 00 06 00 28 06 D0 01 48 01 4A 05 E0
 * 00 00 00 02 9F 3C 00 00 05 48 06 4A 81 18 08 78
 * 01 30 63 28 00 DD 63 20 08 70 30 BC 01 BC 00 47
 * 00 00 00 02 9E 3C 00 00. */
void func_080A215C(SearchContext080A215C *context, void **data)
{
    if (func_080C95A8(13) && func_080C8240(*data)) {
        s32 value;

        if ((u8)func_0809AA10(context)) {
            value = g_state_02000000.counter_3C9F + 1;
            if (value > 99)
                value = 99;
            g_state_02000000.counter_3C9F = value;
        } else {
            value = g_state_02000000.counter_3C9E + 1;
            if (value > 99)
                value = 99;
            g_state_02000000.counter_3C9E = value;
        }
    }
}
