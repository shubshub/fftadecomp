#include "ffta.h"

/* Target [0x080F6490, 0x080F651E), 142 bytes:
 * 70b583b0061c0d1c141c2988012939d0012902dc002908d034e08020400081420ed00130814225d02ce0a88a20706868a060a11c221d0023e7f73ef9e06021e02178012008400223002800d00423a06807490822134300930196002202920c220023e6f777fd20612888013009e00000a8b839082069e5f7a9fa2061002801d102202880002003b070bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F6490;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *coordinate_result;
    void *child;
} Payload080F6490;

extern void *func_080DD748(void *object, s16 *x, s16 *y, u32 mode);
extern void *func_080DCFE4(void *object, const void *record, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DBA5C(void *child);

u32 func_080F6490(void *task, Descriptor080F6490 *descriptor,
                  Payload080F6490 *payload)
{
    u16 flags;

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
        flags = (payload->selector & 1) ? 4 : 2;
        payload->child = func_080DCFE4(payload->object,
            (const void *)0x0839B8A8, 12, 0, flags | 8, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        payload->child = func_080DBA5C(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
