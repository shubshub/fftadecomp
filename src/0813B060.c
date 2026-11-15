#include "ffta.h"

/* Target: complete [0x0813B060, 0x0813B0A8), 72 bytes, 33 instructions.
 * f0b50b1c0006002400220e4f050eff265000c0190188080aa84207d1301c0840
 * 991c09180a70601c0004040c501c0004020c0f2aecd91c802006000ef0bc02bc
 * 08470000b0270003
 * The only caller, 0x0813B57C, passes a 20-byte stack object, which array
 * extents 15 to 18 all produce; 16 is the number of table entries.
 */
typedef struct {
    u16 count;
    u8 indices[16];
} IndexList;

extern u16 data_030027B0[16];

u8 func_0813B060(u8 group, IndexList *output)
{
    u16 count = 0;
    u16 index;

    for (index = 0; index < 16; index++) {
        if ((data_030027B0[index] >> 8) == group) {
            output->indices[data_030027B0[index] & 0xff] = index;
            count++;
        }
    }
    output->count = count;
    return count;
}
