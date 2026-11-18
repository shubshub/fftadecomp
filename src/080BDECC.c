#include "ffta.h"

struct BattleUnit {
    void *actor;
};

extern u8 func_080C48A4(void *source, void *target, u16 action);
extern s32 func_0812E0BC(const void *source, const void *target, u16 action, u8 mode, u32 parameter);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern s32 func_08130200(void *source, void *target, u16 action, u16 equipment, u16 attribute, u16 mode);

/* Complete [0x080BDECC, 0x080BDF9A), 206 bytes. */
s16 func_080BDECC(struct BattleUnit *source, struct BattleUnit *target,
                  u16 action, u16 parameter)
{
    s16 total = 0;
    s16 adjustment;
    u16 equipment[2];
    s16 count, i;

    if (!func_080C48A4(source->actor, target->actor, action))
        return 0;

    adjustment = func_0812E0BC(source->actor, target->actor, action, 1, parameter);
    count = func_0812F0D8(source->actor, equipment);
    if (count == 0) {
        equipment[0] = 0;
        count = 1;
    }
    if (action == 0)
        count = 1;

    for (i = 0; i < count; i++)
        total += func_08130200(source->actor, target->actor, action, equipment[i], 0, 2);

    if (total < 0)
        adjustment = -adjustment;
    return total + adjustment;
}
