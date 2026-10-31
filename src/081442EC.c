#include "ffta.h"

typedef struct {
    u32 significand : 23;
    u32 exponent : 8;
    u32 negative : 1;
} FloatRepresentation;

typedef struct {
    u32 category;
    u32 negative;
    s32 exponent;
    u32 significand;
} FloatParts;

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

typedef union {
    float value;
    FloatRepresentation representation;
} FloatInput;

typedef union {
    FloatParts unpacked;
    UnpackedFloat packed;
} FloatPartsViews;

void func_08143A84(const FloatRepresentation *representation, FloatParts *parts);
float func_081439C8(const UnpackedFloat *number);

/* Complete target: 0x081442EC..0x08144312, 38 bytes.
 * 00b585b0049004a86946fff7c5fb00210198002800d1012101916846fff75efb05b002bc0847
 */
float func_081442EC(float value)
{
    FloatInput input;
    FloatPartsViews parts;

    input.value = value;
    func_08143A84(&input.representation, &parts.unpacked);
    parts.unpacked.negative = !parts.unpacked.negative;
    return func_081439C8(&parts.packed);
}
