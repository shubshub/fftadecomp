#include "ffta.h"

typedef struct AudioState AudioState;

extern u8 func_08141500(void);
extern void func_08145388(AudioState *state, u16 interval);

/* 0x080DFE74 - 68 bytes, including middle and trailing RAM-state literals.
 * Target: 70b50006050e2e1c0c04002c15d061f03dfb0006002810d0210d002900d10121012d
 *         05d1014865f075fa06e0e0f20002022e02d1024865f06dfa70bc01bc004720f30002
 */
void func_080DFE74(u8 channel, u16 duration)
{
    u16 interval;

    if (duration == 0)
        return;
    if (!func_08141500())
        return;
    interval = duration >> 4;
    if (interval == 0)
        interval = 1;
    if (channel == 1)
        func_08145388((AudioState *)0x0200F2E0, interval);
    else if (channel == 2)
        func_08145388((AudioState *)0x0200F320, interval);
}
