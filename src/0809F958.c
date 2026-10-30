#include "ffta.h"

extern const u16 data_08394358[];

/* Complete [0x0809F958, 0x0809F968): 16 bytes.
 * 02494000401800887047000058433908
 */
u16 func_0809F958(u32 index)
{
    return data_08394358[index];
}
