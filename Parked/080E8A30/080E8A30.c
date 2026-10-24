/* 0x080E8A30 .. 0x080E8B24, 244 target bytes
 * f0b584b0071c0e1c151c318880204000814218d0814202dc002909d065e00348
 * 814251d00130814257d05ee001010000b08a28707068e860a91c2a1d0023f4f7
 * 6bfea86051e0e868f4f782fd000600281fd00221685e0422a95e012400942a1c
 * 10320192154a0292039700220123edf7fbfa6861287804400822002c00d01022
 * 0f4804210a43009701210023f7f766f9e8612978012008400222002800d00422
 * e868084900920197002202920c221423f4f780faa8613088013015e088823908
 * bc823908a08239086869edf71bfb686100280ad13088013006e0a869f2f7a6ff
 * a861002801d102203080002004b0f0bc02bc0847
 */
#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *wrapper;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080E8A30;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    void *underlying;
    void *wrapper;
    u8 unknown_10[4];
    void *coordinate_child;
    void *wrapper_child;
    void *record_child;
} Work080E8A30;

extern void *func_080DD748(void *wrapper, s16 *x, s16 *y, s16 *third);
extern u32 func_080DD580(void *wrapper);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                         void *storage, const void *records, void *parent);
extern void *func_080DFD8C(const void *records, u8 count, u16 flags,
                         u16 delay, void *parent);
extern void *func_080DCFE4(void *wrapper, const void *record, u8 count,
                         u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080D6134(void *child);
extern void *func_080DBA5C(void *child);

u32 func_080E8A30(void *task, void *descriptor_data, void *work_data)
{
    Descriptor080E8A30 *descriptor = descriptor_data;
    Work080E8A30 *work = work_data;

    switch (descriptor->phase) {
    case 0:
        work->selector = descriptor->selector;
        work->wrapper = descriptor->wrapper;
        work->underlying = func_080DD748(work->wrapper, &work->x, &work->y, 0);
        break;
    case 0x100:
        if ((u8)func_080DD580(work->wrapper)) {
            work->coordinate_child = func_080D6098(work->x, work->y, 0, 1, 1,
                                                   work->unknown_10,
                                                   (const void *)0x08398288, task);
            work->record_child = func_080DFD8C((const void *)0x083982BC, 1,
                                              4 | (work->selector & 1 ? 16 : 8),
                                              0, task);
        }
        work->wrapper_child = func_080DCFE4(work->wrapper,
                                           (const void *)0x083982A0, 12, 20,
                                           work->selector & 1 ? 4 : 2, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (!work->coordinate_child)
            descriptor->phase++;
        break;
    case 0x102:
        work->wrapper_child = func_080DBA5C(work->wrapper_child);
        if (!work->wrapper_child)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
