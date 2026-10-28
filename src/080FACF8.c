#include "ffta.h"

/* Target 0x080FACF8, complete [0x080FACF8, 0x080FADA6), 174 bytes:
 * 70b584b0061c0d1c141c2988012949d0012902dc002908d044e080204000814211d00130814235d03ce0a88a2070e88a013060806868e060211da21d0023e2f707fda0602ee06088013860800004002828d10421605e0622a15e02220092221c10320192094a0292039600220123dbf797f9a06106480096012104220023e5f709f8e061288801300be0000044cb390894cb3908a069dbf7d1f9a061002801d102202880002004b070bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 delay;
} Descriptor080FACF8;

typedef struct {
    u8 selector;
    u8 unknown_01;
    u16 countdown;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *object;
    u32 unknown_10[2];
    void *coordinate_child;
    void *record_child;
} Payload080FACF8;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);

u32 func_080FACF8(void *task, Descriptor080FACF8 *descriptor,
                  Payload080FACF8 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->countdown = descriptor->delay + 1;
        payload->object = descriptor->object;
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->countdown != 0)
            break;
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_10, (const void *)0x0839CB44, task);
        payload->record_child = func_080DFD8C((const void *)0x0839CB94,
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
