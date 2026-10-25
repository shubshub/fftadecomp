/* Target 0x080E97F4, complete [0x080E97F4, 0x080E991E), 298 bytes:
70b584b0061c0d1c141c2988012900d186e0012902dc002908d081e08020400081421dd0013081426cd079e0a88a2070e88a60700006002809d06868e060211da21df2f7c7fae068f4f714fd68e06868a060211da21d0023f3f77cffe0605fe02178012008400221002800d004210b1c6278002a0cd1a06804490093019602920c220023f3f7b4fb09e00000fc863908e06800960a210c220023f2f741f9e0616078002805d1a068f3f770fe0006002820d00421605e0622a15e02220092221c103201920d4a0292039600220123ecf7e9fba0612178012008400822002800d01022074804210a43009601210023f6f753fa20622888013011e00000cc86390818873908a069ecf71bfca061002807d1e069f2f7a9f8e061002801d102202880002004b070bc02bc0847
*/

#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 selector;
    u16 input_mode;
} Descriptor080E97F4;

typedef struct {
    u8 selector;
    u8 input_mode;
    u8 unknown_02[2];
    s16 coordinate_x;
    s16 coordinate_y;
    void *wrapper;
    void *underlying;
    u8 unknown_10[8];
    void *coordinate_task;
    void *object_task;
    void *record_task;
} Payload080E97F4;

extern void func_080DBDC8(void *object, s16 *coordinate_x, s16 *coordinate_y);
extern void func_080DE268(void *object);
extern void *func_080DD748(void *wrapper, s16 *coordinate_x,
                          s16 *coordinate_y, s16 *coordinate_z);
extern void *func_080DCFE4(void *wrapper, const void *record, u8 count,
                          u16 delay, u16 flags, void *parent, s16 value);
extern void *func_080DBB14(void *object, u8 first, u8 second, u16 value,
                          void *parent);
extern u32 func_080DD580(const void *wrapper);
extern void *func_080D6098(s16 coordinate_x, s16 coordinate_y,
                          s16 coordinate_z, u8 mode, u16 count,
                          void *storage, const void *record, void *parent);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_080D6134(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080E97F4(void *task, Descriptor080E97F4 *descriptor,
                  Payload080E97F4 *payload)
{
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->input_mode = descriptor->input_mode;
        if (payload->input_mode != 0) {
            payload->underlying = descriptor->object;
            func_080DBDC8(payload->underlying, &payload->coordinate_x,
                         &payload->coordinate_y);
            func_080DE268(payload->underlying);
        } else {
            payload->wrapper = descriptor->object;
            payload->underlying = func_080DD748(payload->wrapper,
                &payload->coordinate_x, &payload->coordinate_y, 0);
        }
        break;
    case 1:
        break;
    case 0x100:
        flags = (payload->selector & 1) ? 4 : 2;
        if (payload->input_mode == 0)
            payload->object_task = func_080DCFE4(payload->wrapper,
                (const void *)0x083986FC, 12, 0, flags, task, 0);
        else
            payload->object_task = func_080DBB14(payload->underlying,
                                               10, 12, 0, task);
        if (payload->input_mode != 0 || (u8)func_080DD580(payload->wrapper) != 0) {
            payload->coordinate_task = func_080D6098(payload->coordinate_x,
                payload->coordinate_y, 0, 1, 2, payload->unknown_10,
                (const void *)0x083986CC, task);
            flags = (payload->selector & 1) ? 16 : 8;
            payload->record_task = func_080DFD8C((const void *)0x08398718,
                1, flags | 4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
