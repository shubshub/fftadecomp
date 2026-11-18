#include "ffta.h"

struct FlashSector {
    u32 size;
    u8 shift;
    u16 count;
    u16 top;
};

struct FlashType {
    u32 romSize;
    struct FlashSector sector;
    u16 wait[2];
    union {
        struct {
            u8 makerId;
            u8 deviceId;
        } separate;
        u16 joined;
    } ids;
};

extern const struct FlashType *data_0200F370;

/* Return how many sector bytes remain from the first non-erased byte. */
u32 func_08142124(const u8 *bytes)
{
    u32 remaining = data_0200F370->sector.size;

    while (remaining != 0 && *bytes++ == 0xFF)
        remaining--;
    return remaining;
}
