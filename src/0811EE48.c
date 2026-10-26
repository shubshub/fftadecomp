#include "ffta.h"

/* Target: complete [0x0811EE48, 0x0811EF56), 270 bytes including literals. */
typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    s16 x;
    s16 y;
    u16 index;
} Descriptor0811EE48;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation0811EE48;

typedef struct {
    u16 flags;
    u8 unknown_02[6];
    void *object;
    u8 index;
    u8 motion;
    u16 unknown_0e;
    Interpolation0811EE48 x_motion;
    Interpolation0811EE48 y_motion;
} Payload0811EE48;

typedef struct {
    u8 duration;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
} Motion0811EE48;

extern const u8 data_083A75A8[];
extern const u8 data_083A75E8[];
extern const u8 data_083A7628[];
extern const u8 data_085087D8[];
extern const Motion0811EE48 data_083A7668[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011058(void *, s16);
extern void func_08011138(void *, u8);
extern void func_080E0608(Interpolation0811EE48 *, s16, s16, s16);
extern void func_080E064C(Interpolation0811EE48 *);
extern void func_080107D4(void *, s16, s16, u8);
extern void *func_08011484(void *);

u32 func_0811EE48(void *task, Descriptor0811EE48 *descriptor,
                  Payload0811EE48 *payload)
{
    s16 x;
    s16 y;

    if (payload->flags & 0x8000)
        return 0;

    switch (descriptor->phase) {
    case 0:
        payload->index = descriptor->index;
        payload->motion = data_083A75A8[payload->index];
        x = descriptor->x + data_083A75E8[payload->index];
        y = descriptor->y + data_083A7628[payload->index];
        payload->object = func_080D5CC0(data_085087D8, 2, x, y, 972, 6, 0, 0);
        func_08011058(payload->object, -1);
        func_08011138(payload->object, 1);
        func_080E0608(&payload->x_motion, x,
                      x + data_083A7668[payload->motion].x,
                      data_083A7668[payload->motion].duration);
        func_080E0608(&payload->y_motion, y,
                      y + data_083A7668[payload->motion].y,
                      data_083A7668[payload->motion].duration);
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
