#include "ffta.h"

extern void func_08019A50(u16 value, u8 *id, u16 *offset);
extern void func_0801174C(void *context, u8 kind, u16 selection,
                          void *first, void *second, u32 field5, s32 field6,
                          u32 width, u32 height, u32 tile);
extern void func_0801339C(u16 value);

/* Complete target [0x08019AE4, 0x08019B48): 100 bytes, 47 instructions.
 * 70b54e46454660b487b08046081c91461e1c0d9c0004000c2404240c6d461a35
 * 06a92a1cfff7a2ff06a801782a880096022001902404241402941820039004200490
 * e8208000059040464b46f7f70cfe0220f9f731fc07b018bc9846a14670bc01bc0047
 */
void func_08019AE4(void *context, u16 value, void *first, void *second,
                   u16 field)
{
    u8 id;
    u16 offset;

    func_08019A50(value, &id, &offset);
    func_0801174C(context, id, offset, first, second, 2, (s16)field,
                  24, 4, 0x3A0);
    func_0801339C(2);
}
