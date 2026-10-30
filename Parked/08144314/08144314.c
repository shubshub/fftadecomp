#include "ffta.h"

typedef enum {
    FP_SNAN,
    FP_QNAN,
    FP_ZERO,
    FP_NUMBER,
    FP_INFINITY
} FloatClass;

typedef struct {
    FloatClass classification;
    u32 sign;
    s32 exponent;
    u32 fraction;
} UnpackedFloat;

extern float func_081439C8(const UnpackedFloat *number);

/* Complete target [0x08144314, 0x0814432C), 24 bytes.
 * Target: 00b584b000900191029203936846fff751fb04b002bc0847.
 */
float func_08144314(FloatClass classification, u32 sign, s32 exponent, u32 fraction)
{
    UnpackedFloat number;

    number.classification = classification;
    number.sign = sign;
    number.exponent = exponent;
    number.fraction = fraction;
    return func_081439C8(&number);
}
