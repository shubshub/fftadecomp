#include "ffta.h"

/* Target 0x080F7EC0, complete [0x080F7EC0, 0x080F7F6E), 174 bytes:
 * 70b584b0061c0d1c141c2988012949d0012902dc002908d044e080204000814211d00130814235d03ce0a88a2070e88a013060806868e060211da21d0023e5f723fca0602ee06088013860800004002828d10421605e0622a15e02220092221c10320192094a0292039600220123def7b3f8a06106480096012104220023e7f725ffe061288801300be0000080be3908dcbe3908a069def7edf8a061002801d102202880002004b070bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u16 selector;
    u16 delay;
} Descriptor080F7EC0;

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
} Payload080F7EC0;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);

u32 func_080F7EC0(void *task, Descriptor080F7EC0 *descriptor,
                  Payload080F7EC0 *payload)
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
            0, 1, 2, payload->unknown_10, (const void *)0x0839BE80, task);
        payload->record_child = func_080DFD8C((const void *)0x0839BEDC,
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
