/* Target bytes (12):
 * 01 49 40 18 00 78 70 47 97 07 00 00
 */
#include "ffta.h"

struct ObjectStateAt797 {
    u8 unknown_000[0x797];
    u8 value_797;
};

u8 func_0802B548(struct ObjectStateAt797 *object)
{
    return object->value_797;
}
