#include "ffta.h"

struct Entry080D3B98 {
    u8 unknown_00[6];
    u8 type;
    u8 unknown_07;
};

extern const struct Entry080D3B98 data_083947D8[];
extern void *func_080DD47C(void *object);
extern void *func_080DD478(const void *object);
extern u8 func_080C8384(const void *object);

/* Complete [0x080D3B98, 0x080D3BCE): 54 bytes, 22 instructions. */
u8 func_080D3B98(void *object, u16 entry_index)
{
    if (data_083947D8[entry_index - 1].type == 16 &&
        !func_080C8384(func_080DD478(func_080DD47C(object))))
        return 1;
    return 0;
}
