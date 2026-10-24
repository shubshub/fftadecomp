#include "ffta.h"

/* Target 0x080EA1F8, 222 owned bytes:
 * f0b584b0061c0d1c141c2988012961d0012902dc002908d05ce08020400081420ed00130814247d054e0a88a20706868a060211da21d0023f3f78afae06049e00421605e0622a15e04220092221c10320192174a0292039600220123ebf720ff206221780127381c08400221002800d00421a068009101963221029100210c220023f2f7b3fe60622178381c08400822002800d01022074804210a43009601210023f5f777fda0622888013011e00000f888390858893908206aebf73fff2062002807d1606af1f7cdfb6062002801d102202880002004b0f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *wrapper;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080EA1F8;

typedef struct {
    u8 selector;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *wrapper;
    void *object;
    u8 unknown_10[16];
    void *coordinate_child;
    void *wrapper_child;
    void *record_child;
} Work080EA1F8;

extern void *func_080DD748(void *wrapper, s16 *x, s16 *y, s16 *z);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                         void *buffer, const void *records, void *parent);
extern void *func_080DCFE4(void *wrapper, const void *records, u8 mode,
                         u16 value, u16 flags, void *parent, s16 fallback);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080EA1F8(void *task, void *descriptor_data, void *work_data)
{
    Descriptor080EA1F8 *descriptor = descriptor_data;
    Work080EA1F8 *work = work_data;
    u16 wrapper_flags;
    u16 record_flags;

    switch (descriptor->phase) {
    case 0:
        work->selector = descriptor->selector;
        work->wrapper = descriptor->wrapper;
        work->object = func_080DD748(work->wrapper, &work->x, &work->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        work->coordinate_child = func_080D6098(work->x, work->y, 0, 1, 4,
                                             work->unknown_10,
                                             (const void *)0x083988F8, task);
        wrapper_flags = work->selector & 1 ? 4 : 2;
        work->wrapper_child = func_080DCFE4(work->wrapper, 0, 12, 0,
                                          wrapper_flags, task, 50);
        record_flags = work->selector & 1 ? 16 : 8;
        work->record_child = func_080DFD8C((const void *)0x08398958, 1,
                                         record_flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (work->coordinate_child != 0)
            break;
        work->wrapper_child = func_080DBA5C(work->wrapper_child);
        if (work->wrapper_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
