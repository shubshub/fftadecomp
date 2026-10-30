#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject0802C7E0;

typedef struct {
    u8 unknown_00[0x62];
    u16 field_62;
    u16 field_64;
    u8 unknown_66[0x1E];
    u16 field_84;
    u8 unknown_86[0x1E];
    u16 field_a4;
} State0802C7E0;

extern u8 func_080C82B8(const FlaggedObject0802C7E0 *object);
extern u8 func_080C832C(const FlaggedObject0802C7E0 *object);

/* Complete target: [0x0802C7E0, 0x0802C830), 80 bytes. */
void func_0802C7E0(State0802C7E0 *state,
                  const FlaggedObject0802C7E0 *object)
{
    if (func_080C82B8(object)) {
        u32 value = 0xD0D8;

        state->field_62 = value++;
        state->field_84 = value++;
        state->field_64 = value;
    }
    if (func_080C832C(object)) {
        u32 value = 0xD0D7;

        state->field_a4 = value;
    }
}
