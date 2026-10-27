#include "ffta.h"

typedef struct {
    u32 value;
    u8 unknown_04[0x0C];
} SlotRecord;

extern u8 g_state_02000000[];
extern s32 func_080C9428(const void *object);

/* Target: [0x0812F124, 0x0812F152), 46 bytes, 18 instructions. */
SlotRecord *func_0812F124(const void *object)
{
    s32 index = func_080C9428(object);

    if (index >= 0) {
        u8 *base = g_state_02000000;
        u32 offset = index * sizeof(SlotRecord);
        const u8 *record = base + offset;

        if (*(const u32 *)(record + 0x2E78) == 0)
            return &((SlotRecord *)(base + 0x2E78))[index];
    }
    return 0;
}
