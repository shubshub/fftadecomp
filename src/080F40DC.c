#include "ffta.h"

/* Target 0x080F40DC, complete [0x080F40DC, 0x080F41C8), 236 bytes:
 * f0b584b0061c0d1c141c298880204000814218d0814202dc002909d061e0034881424dd00130814253d05ae001010000a88a20706868e060a11c221d0023e9f715fba0604de00221605e0422a15e03220092221c10320192164a0292039600220123e1f7abffe06121780127381c08400222002800d00422e0680f49009201962a2202920c222a23e8f73eff20622178381c08400822002800d01022074804210a43009601210023ebf702fe60622888013015e0c0af390808b039082cb03908e069e1f7c9ffe06100280ad12888013006e0206ae7f754fc2062002801d102202880002004b0f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F40DC;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *coordinate_result;
    void *object;
    u32 unknown_10;
    u32 unknown_14;
    u32 unknown_18;
    void *coordinate_child;
    void *object_child;
    void *record_child;
} Payload080F40DC;

extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080F40DC(void *task, Descriptor080F40DC *descriptor,
                  Payload080F40DC *payload)
{
    u16 object_flags;
    u16 record_flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, &payload->unknown_10, (const void *)0x0839AFC0, task);
        object_flags = payload->selector & 1 ? 4 : 2;
        payload->object_child = func_080DCFE4(payload->object,
            (const void *)0x0839B008, 12, 42, object_flags, task, 42);
        record_flags = payload->selector & 1 ? 16 : 8;
        payload->record_child = func_080DFD8C((const void *)0x0839B02C,
            1, record_flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child == 0)
            descriptor->phase++;
        break;
    case 0x102:
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
