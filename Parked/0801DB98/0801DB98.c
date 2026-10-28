#include "ffta.h"

typedef struct {
    u8 unknown_00[0x54];
    u8 normal;
    u8 alternate;
    u8 unknown_56[2];
} ResourceRecord;

extern u16 data_02007F10;
extern const ResourceRecord data_08569104[];
extern u8 func_0801AE9C(void);

/* Complete [0x0801DB98, 0x0801DC04): 108 bytes, 47 instructions. */
u8 func_0801DB98(u16 index)
{
    u8 result;

    if ((s16)index == -1)
        index = data_02007F10;
    result = 0xFF;
    if ((s16)index != 0xFF) {
        u8 use_alternate = 0;

        if (func_0801AE9C() != 0)
            use_alternate = data_08569104[(s16)index].alternate != 0xFF;
        if (use_alternate == 0)
            result = data_08569104[(s16)index].normal;
        else
            result = data_08569104[(s16)index].alternate;
    }
    return result;
}
