#include "ffta.h"

typedef struct {
    const void *record;
    u8 unknown_04[0x22];
    u16 flags;
} State0813158C;

extern u32 func_08002804(void);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* Complete 0x0813158C..0x081315D2, 70 bytes:
 * 30b5051ce98c10200840002814d1d1f633f900040014074911f0d4f9000404148034
 * 2868142196f777fc6043040a201c06e00000010100002868142196f76cfc30bc02bc0847
 */
u32 func_0813158C(const State0813158C *state)
{
    if (!(state->flags & 0x10)) {
        u32 factor = (s16)((s16)func_08002804() % 257) + 128;

        return ((u32)func_080C7EA4(state->record, 0x14) * factor) >> 8;
    }
    return func_080C7EA4(state->record, 0x14);
}
