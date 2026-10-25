#include "ffta.h"

/* Target [0x080E75B8, 0x080E76A2), 234 bytes:
f0b584b0071c0e1c151c3188012967d0012902dc002908d062e08020400081420ed0013081424dd05ae0b08a28707068a860291daa1d0023f6f7aaf8e8604fe0a868f5f7c1ff000600281fd00421685e0622a95e012400942a1c10320192164a0292039700220123eef73afd6861287804400822002c00d01022104804210a43009701210023f8f7a5fbe8612978012008400222002800d00422a8680849009201970a2202920c220a23f5f7bffca8613088013013e00000c8783908307a39080c7a39086869eef759fd6861002807d1a869f4f7e7f9a861002801d102203080002004b0f0bc02bc0847
*/

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 flags;
} EffectDescriptor;

typedef struct {
    u8 flags;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *object;
    void *underlying;
    u8 unknown_10[4];
    void *coordinate_child;
    void *wrapper_child;
    void *record_child;
} EffectWork;

extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern u32 func_080DD580(void *object);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                         void *buffer, const void *records, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void *func_080DCFE4(void *object, const void *records, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080D6134(void *child);
extern void *func_080DBA5C(void *child);

u32 func_080E75B8(void *task, void *descriptor_data, void *work_data)
{
    EffectDescriptor *descriptor = descriptor_data;
    EffectWork *work = work_data;
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        work->flags = descriptor->flags;
        work->object = descriptor->object;
        work->underlying = func_080DD748(work->object, &work->x, &work->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        if ((u8)func_080DD580(work->object) != 0) {
            work->coordinate_child = func_080D6098(work->x, work->y, 0, 1, 1,
                                                 work->unknown_10,
                                                 (const void *)0x083978C8, task);
            flags = (work->flags & 1) ? 0x10 : 8;
            work->record_child = func_080DFD8C((const void *)0x08397A30, 1,
                                              flags | 4, 0, task);
        }
        flags = (work->flags & 1) ? 4 : 2;
        work->wrapper_child = func_080DCFE4(work->object, (const void *)0x08397A0C,
                                           12, 10, flags, task, 10);
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
