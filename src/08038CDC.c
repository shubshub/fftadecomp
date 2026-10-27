#include "ffta.h"

typedef struct {
    u8 entry;
    u8 unknown_01[3];
} RenderChoice;

extern const RenderChoice data_08391CA4[];

/* 08038CDC..08038CF0: 20 bytes, 7 instructions. */
u8 func_08038CDC(u8 choice)
{
    return data_08391CA4[choice - 1].entry;
}
