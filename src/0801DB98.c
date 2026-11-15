#include "ffta.h"

typedef struct __attribute__((packed)) {
    u8 unknown_00[0x50];
    u32 resource_offset;
    u8 normal;
    u8 alternate;
    u8 unknown_56[2];
} ResourceRecord;

typedef struct {
    u16 selected;
} ResourceSelection;

extern ResourceSelection data_02007F10;
extern const ResourceRecord data_08569104[];
extern u8 func_0801AE9C(void);

/* Complete [0x0801DB98, 0x0801DC04): 108 bytes, 47 instructions. */
u8 func_0801DB98(s16 index)
{
    u8 result;

    if (index == -1)
        index = data_02007F10.selected;
    result = 0xFF;
    if (index != 0xFF) {
        u8 use_alternate = 0;

        if (func_0801AE9C() != 0)
            use_alternate = data_08569104[index].alternate != 0xFF;
        if (use_alternate == 0)
            result = data_08569104[index].normal;
        else
            result = data_08569104[index].alternate;
    }
    return result;
}
