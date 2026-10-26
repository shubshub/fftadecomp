#include "ffta.h"

/* Target: complete [0x08133CC8, 0x08133D78), 176 bytes. */
extern s32 func_080C7EA4(const void *, u32);
extern const u8 *func_080CD480(u8, u8);
extern u16 func_08133C00(u16);
extern u32 func_080CCD50(u16, u8);

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 unknown_07[0x2d];
    u8 limit;
    u8 unknown_35[11];
    u8 progress[256];
} ProgressRecord;

u16 func_08133CC8(const u8 **output, const ProgressRecord *object)
{
    u32 limit = object->limit;
    u32 count = 0;
    u16 index;

    for (index = 1; index < limit; index++) {
        const u8 *entry = func_080CD480(func_080C7EA4(object, 3), index);

        if (entry[6] == 1 &&
            !func_08133C00(*(const u16 *)(entry + 4)) &&
            func_080CCD50(*(const u16 *)(entry + 4), 0x19) &&
            !func_080CCD50(*(const u16 *)(entry + 4), 0x16)) {
            u32 progress = object->progress[index] & 0x7f;
            const u8 *requirement = func_080CD480(object->type, index);

            if (progress >= requirement[7]) {
                *output++ = entry;
                count++;
            }
        }
    }
    return count;
}
