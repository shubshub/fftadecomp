#include "ffta.h"

typedef struct AudioState AudioState;

extern u8 func_08141500(void);
extern void func_0814164C(u16 channel);
extern void func_08145358(AudioState *state, u16 interval);

/* 0x080DFE28 - 76 bytes, including two RAM-address literals.
 * Target: 70b50006040e261c0d04002d03d1201c61f008fc15e061f05ffb0006002810d0290d
 *         002900d10121012c05d1014865f07ffa06e0e0f20002022e02d1024865f077fa70bc
 *         01bc004720f30002
 */
void func_080DFE28(u8 channel, u16 duration)
{
    u16 interval;

    if (duration == 0) {
        func_0814164C(channel);
        return;
    }
    if (func_08141500() == 0)
        return;
    interval = duration >> 4;
    if (interval == 0)
        interval = 1;
    if (channel == 1)
        func_08145358((AudioState *)0x0200F2E0, interval);
    else if (channel == 2)
        func_08145358((AudioState *)0x0200F320, interval);
}
