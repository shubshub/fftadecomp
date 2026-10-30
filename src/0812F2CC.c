#include "ffta.h"

extern u8 func_08130834(void *unit);
extern u8 func_08130868(void *unit, void *target);
extern u8 func_08133970(u8 kind);

/* Complete 0x0812F2CC..0x0812F328, 92 bytes:
 * 70b5061c0d1c141c281c01f0adfa000600281fd0301c291c01f0c0fa0006002818d0
 * 2006000e04f03dfb0006000e00280ed0002803db082801dc062808da442c06d0442c
 * 02dc272c02d003e04a2c01d1002000e0012070bc02bc0847
 */
u8 func_0812F2CC(void *source, void *target, s32 kind)
{
    if (!func_08130834(target) || !func_08130868(source, target))
        return 1;

    switch (func_08133970((u8)kind)) {
    case 0:
    case 6:
    case 7:
    case 8:
        return 0;
    }

    switch (kind) {
    case 0x27:
    case 0x44:
    case 0x4A:
        return 0;
    }
    return 1;
}
