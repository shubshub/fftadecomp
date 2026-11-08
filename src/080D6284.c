/* 0x080D6284: complete 72-byte caller, including the callback literal.
 * f0b5474680b48eb0149c159d169e179fb846189f0090019102926846038303940495
 * 059607aa404690826846506005484c213b1c2ff758fc0eb008bc9846f0bc02bc0847
 * 95550d08
 */
#include "ffta.h"

typedef Struct08011040 Object;
typedef struct { Object *object; } ObjectHandle;

typedef union {
    struct { s16 x, y, z, unknown_06; } component;
    u32 xy;
} Position;

typedef struct {
    ObjectHandle *object;
    Position *start;
    Position *end;
    s16 *x_curve;
    s16 *y_curve;
    s16 *z_curve;
    u16 delay;
    u16 unknown_1A;
} Parameters;

typedef struct {
    u16 phase;
    u16 unknown_02;
    const Parameters *parameters;
    u8 unknown_08[12];
    u16 flags;
    u8 unknown_16[6];
} Descriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D5594(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D6284(ObjectHandle *object, Position *start, Position *end,
                    u16 delay, s16 *x_curve, s16 *y_curve,
                    s16 *z_curve, u16 flags, void *parent)
{
    Parameters parameters;
    Descriptor descriptor;

    parameters.object = object;
    parameters.start = start;
    parameters.end = end;
    parameters.delay = delay;
    parameters.x_curve = x_curve;
    parameters.y_curve = y_curve;
    parameters.z_curve = z_curve;
    descriptor.flags = flags;
    descriptor.parameters = &parameters;
    return func_08005B6C(func_080D5594, 0x4C, &descriptor, parent);
}
