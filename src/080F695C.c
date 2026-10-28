#include "ffta.h"

/* Target 0x080F695C, complete [0x080F695C, 0x080F6A3E), 226 bytes:
 * f0b584b0061c0d1c141c2988012963d0012902dc002908d05ee08020400081420ed00130814249d056e0a88a20706868a060a11c221d0023e6f7d8fee0604be00221605e0422a15e03220092221c10320192174a0292039600220123dff76efbe06121780127381c08400222002800d00422a0680f4900920196182202920c221823e6f701fb20622178381c08400822002800d01022084804210a43009601210023e9f7c5f960622888013013e0000070b93908d0b93908f0b93908e069dff78bfbe061002807d1206ae5f719f82062002801d102202880002004b0f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F695C;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *coordinate_result;
    u32 unknown_10[3];
    void *coordinate_child;
    void *object_child;
    void *record_child;
} Payload080F695C;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080F695C(void *task, Descriptor080F695C *descriptor,
                  Payload080F695C *payload)
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
    case 1:
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_10, (const void *)0x0839B970, task);
        object_flags = payload->selector & 1 ? 4 : 2;
        payload->object_child = func_080DCFE4(payload->object,
            (const void *)0x0839B9D0, 12, 24, object_flags, task, 24);
        record_flags = payload->selector & 1 ? 16 : 8;
        payload->record_child = func_080DFD8C((const void *)0x0839B9F0,
            1, record_flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
