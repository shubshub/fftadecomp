#include "ffta.h"

typedef void (*Callback08022DD0)(u8, u8 *);

typedef struct {
    u8 unknown_00[8];
    Callback08022DD0 *callbacks;
    u8 *flags;
} Table08022DD0;

extern Table08022DD0 data_03002710;
extern const u8 data_08149994[2];
extern void *func_081443FC(void *, const void *, u32);

// Complete target [0x08022DD0, 0x08022E24): 84 bytes, 42 instructions.
void func_08022DD0(void)
{
    u8 order[2];
    s32 i;

    func_081443FC(order, data_08149994, 2);
    for (i = 0; i <= 1; i++) {
        u32 index = order[i];

        if (data_03002710.callbacks[index] != 0) {
            data_03002710.flags[index] = 0xff;
            data_03002710.callbacks[index](index, &data_03002710.flags[index]);
        }
    }
}
