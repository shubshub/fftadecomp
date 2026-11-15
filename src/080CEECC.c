#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

typedef struct {
    u8 unknown_0000[0x21B4];
    u8 slots[16][2];
    u8 unknown_21D4[0x2B08 - 0x21D4];
    SlotEntry entries[64];
} State080CEECC;

extern State080CEECC g_state_02000000;

u32 func_080CE4DC(u16 index, u8 selector);

/* Complete target: [0x080CEECC, 0x080CEF78), 172 bytes. */
u32 func_080CEECC(u16 index)
{
    u16 required = func_080CE4DC(index, 42);
    s32 slot;

    if (required != 0) {
        for (slot = 0; slot < 64; slot++) {
            if (g_state_02000000.entries[slot].value == required)
                break;
        }
        if (slot == 64)
            return 0;
    }
    required = func_080CE4DC(index, 44);
    if (required != 0) {
        for (slot = 0; slot < 64; slot++) {
            if (g_state_02000000.entries[slot].value == required)
                break;
        }
        if (slot == 64)
            return 0;
    }
    required = func_080CE4DC(index, 46);
    if (required != 0) {
        if (g_state_02000000.slots[required][0] < func_080CE4DC(index, 47))
            return 0;
    }
    return 1;
}
