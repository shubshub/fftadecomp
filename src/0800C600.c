#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0E];
    u16 selector;
    u8 unknown_10[8];
    u32 primary;
    u32 fallback;
} Object0800C600;

/* 0x0800C600 - 20 bytes.
 * Target: 00b5011cc889002801d1c86900e0886902bc0847
 */
u32 func_0800C600(const Object0800C600 *object)
{
    if (object->selector != 0)
        return object->primary;
    return object->fallback;
}
