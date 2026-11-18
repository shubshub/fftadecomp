#include "ffta.h"

/* Action evaluator slot 2, 0x081314D0..0x081314FC.
 * 10b5041c60689cf7b9fa0006002809d0206b4078152803d0082801d00f2801d1002000e01e2010bc02bc0847
 */
struct ActionRecord {
    u8 unknown00;
    u8 kind;
};

struct ActionState {
    void *source;
    void *target;
    u8 unknown08[0x28];
    struct ActionRecord *record;
};

extern u8 func_080CDA4C(const void *object);

s32 func_081314D0(struct ActionState *state)
{
    if (func_080CDA4C(state->target)) {
        u8 kind = state->record->kind;
        if (kind == 0x15 || kind == 8 || kind == 0x0F)
            return 0;
    }
    return 30;
}
