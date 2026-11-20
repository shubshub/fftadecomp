#include "ffta.h"

/* Target: 0x0808F804, complete 68-byte Thumb function. */
typedef struct FlaggedValue {
    u32 flags;
    u8 unknown_04[0x24];
    u32 value;
} FlaggedValue;

typedef struct CallbackPosition {
    s16 x;
    s16 y;
    u16 state;
} CallbackPosition;

typedef s32 (*PositionCallback)(const u8 *data, s32 x, s32 y, u8 flip_x, u8 flip_y);
extern PositionCallback g_object_08394028;

u32 func_08021DA8(const FlaggedValue *object, u8 *first, u8 *second);

void func_0808F804(const FlaggedValue *object, CallbackPosition *position)
{
    u8 first;
    u8 second;
    u32 value = func_08021DA8(object, &first, &second);

    if (value) {
        if (g_object_08394028((const u8 *)value, position->x, position->y,
                              first, second) == 1)
            position->state = 1;
    }
}
