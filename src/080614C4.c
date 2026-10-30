#include "ffta.h"

typedef struct {
    const void *record;
} State;

extern State g_state_020020D0;

u32 func_080CF310(const void *record, const void *object, u8 enabled);

/* 080614C4..08061516: 82 bytes.
 * 10b5011c00240648006800226df01eff05281ad8800003494018006887460000
 * d0200002ec1406080c150608041506080415060808150608081506080c150608
 * 182402e0002400e00c24201c10bc02bc0847
 */
u32 func_080614C4(const void *object)
{
    u32 result = 0;

    switch (func_080CF310(g_state_020020D0.record, object, 0)) {
    case 1:
    case 2:
        result = 24;
        break;
    case 3:
    case 4:
        result = 0;
        break;
    case 0:
    case 5:
        result = 12;
        break;
    }
    return result;
}
