#include "ffta.h"

/* Target: complete [0x0811ED40, 0x0811EE46), 262 bytes, 111 instructions.
 * These structures describe observed offsets, not complete object extents. */
typedef struct {
    u16 phase;
    u8 unknown_02[18];
    s16 x;
    s16 y;
    u16 selector;
} Descriptor0811ED40;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion0811ED40;

typedef struct {
    u16 flags;
    u8 unknown_02[6];
    void *object;
    u8 selector;
    u8 motion_index;
    u8 unknown_0e[2];
    Motion0811ED40 x_motion;
    Motion0811ED40 y_motion;
} Payload0811ED40;

typedef struct {
    u8 duration;
    u8 unknown_01;
    s16 x_offset;
    s16 y_offset;
    u16 unknown_06;
} MotionParameters0811ED40;

extern const u8 data_083A7546[];
extern const u8 data_083A755C[];
extern const u8 data_083A7572[];
extern const u8 data_085087D8[];
extern const u8 data_083A7530[];
extern const MotionParameters0811ED40 data_083A7588[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_080E0608(Motion0811ED40 *, s16, s16, s16);
extern void func_080E064C(Motion0811ED40 *);
extern void func_080107D4(void *, s16, s16, u8);
extern void *func_08011484(void *);

u32 func_0811ED40(void *task, Descriptor0811ED40 *descriptor,
                  Payload0811ED40 *payload)
{
    if (payload->flags & 0x8000)
        return 0;

    switch (descriptor->phase) {
    case 0:
        {
            s16 x, y;

            payload->selector = descriptor->selector;
            payload->motion_index = data_083A7546[payload->selector];
            x = descriptor->x + data_083A755C[payload->selector];
            y = descriptor->y + data_083A7572[payload->selector];
            payload->object = func_080D5CC0(
                data_085087D8, data_083A7530[payload->selector],
                x, y, 0x3cc, 6, 0, 0);
            func_080E0608(&payload->x_motion, x,
                x + data_083A7588[payload->motion_index].x_offset,
                data_083A7588[payload->motion_index].duration);
            func_080E0608(&payload->y_motion, y,
                y + data_083A7588[payload->motion_index].y_offset,
                data_083A7588[payload->motion_index].duration);
        }
        break;
    case 1:
        break;
    case 0x100:
        func_080E064C(&payload->x_motion);
        func_080E064C(&payload->y_motion);
        func_080107D4(payload->object, payload->x_motion.current,
                      payload->y_motion.current, 0);
        payload->object = func_08011484(payload->object);
        if (payload->object == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
