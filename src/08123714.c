#include "ffta.h"

/* Complete [0x08123714, 0x08123770), 92 bytes.
 * Target: f0b5071c0c798d78c878000205434a78002600210123201c08411840002800d01643013112020329f5dd01202040002807d0002e05d0fef727fb0006000e1df0e9ff2a04120c381c311c231c04f054fc0148f0bc02bc084715010000 */
u8 func_08121D9C(void);
void func_08141728(u16 value);
void func_0812800C(void *context, u32 target, u16 duration, u8 channels);

u32 func_08123714(void *context, const u8 *script)
{
    u8 value = script[1];
    u8 channels = script[4];
    u32 duration = script[2] | (script[3] << 8);
    u32 lane = value;
    u32 target = 0;
    int index;

    for (index = 0; index < 4; index++, lane <<= 8) {
        if ((channels >> index) & 1)
            target |= lane;
    }

    if ((channels & 1) && target != 0)
        func_08141728(func_08121D9C());
    func_0812800C(context, target, duration, channels);
    return 0x115;
}
