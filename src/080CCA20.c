#include "ffta.h"

/* Complete [0x080CCA20, 0x080CCA54): 52 bytes, 22 instructions.
 * 00b50004010c081caa2907d90248ab3989000918087809e05c473908044a5529
 * 01d9081c553800011018007802bc0847348f5208
 */

typedef struct {
    u8 value;
    u8 unknown_01[3];
} ExtraEntry;

typedef struct {
    u8 value;
    u8 unknown_01[15];
} BaseEntry;

extern const ExtraEntry data_0839475C[];
extern const BaseEntry g_table_08528F34[];

u8 func_080CCA20(u16 entry)
{
    if (entry > 0xAA)
        return data_0839475C[entry - 0xAB].value;
    return g_table_08528F34[entry > 0x55 ? entry - 0x55 : entry].value;
}
