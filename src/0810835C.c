#include "ffta.h"

/* Target: complete [0x0810835C, 0x081083EA), 142 bytes, 65 instructions.
 * These local offset views do not establish original types or storage extents.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 mode;
} Descriptor0810835C;

typedef struct {
    u8 mode;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *actor;
    void *coordinate_result;
    void *effect_child;
} Payload0810835C;

/* Address binding only; the original data declaration and extent are unknown. */
extern const u8 data_083A0F20[];

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DBA5C(void *);

u32 func_0810835C(void *task, Descriptor0810835C *descriptor,
                  Payload0810835C *payload)
{
    u16 mode;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->actor = descriptor->actor;
        payload->coordinate_result = func_080DD748(payload->actor,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        mode = (payload->mode & 1) ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->actor, data_083A0F20,
            12, 0, mode | 8, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
