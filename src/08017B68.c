/* 0x08017B68 - 52 bytes (the index span of 20 is truncated; the function runs
 * to the epilogue at 0x08017B9C).
 *
 * Clamps (s8)index + field_1A into [0, field_18 - 1] and returns the result.
 * Same body as the sibling at 0x08017B9C, which continues into a call.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

u16 func_08017B68(ClampState08017B68 *state, u32 index) {
    s16 value = (s8)index + state->field_1A;

    if (value < 0) {
        return 0;
    } else if (value > (s16)state->field_18 - 1) {
        return state->field_18 - 1;
    } else {
        return value;
    }
}