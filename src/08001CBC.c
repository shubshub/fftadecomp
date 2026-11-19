#include "oam_lists.h"

/* Complete [0x08001CBC, 0x08001CD0): 20 bytes: 6 instructions and two literal
 * words.
 * Target: 02480078c001024940187047582f000370310003.
 */
u64 *func_08001CBC(void)
{
    return data_03003170[data_03002F58];
}
