#include "ffta.h"

typedef struct Unit080924F4 Unit080924F4;
typedef struct Context080924F4 Context080924F4;
typedef struct {
    Unit080924F4 *unit;
} Entry080924F4;

extern u8 func_080C95A8(u16 flag);
extern u8 func_0809A9F0(Context080924F4 *context, Unit080924F4 *unit);
extern u8 func_080CDB54(Unit080924F4 *unit);
extern u8 func_080CDB6C(Unit080924F4 *unit);
extern u8 func_080CD944(Unit080924F4 *unit);
extern u8 func_080C8260(Unit080924F4 *unit);
extern Entry080924F4 *func_080970E8(Context080924F4 *context, Unit080924F4 *unit);
extern u8 func_080C8240(Unit080924F4 *unit);
extern u8 func_080C8298(Unit080924F4 *unit);

/* Complete [0x080924F4, 0x080925A2): 174 bytes, 75 instructions. */
u8 func_080924F4(Unit080924F4 *unit, Context080924F4 *context)
{
    Entry080924F4 *entry;
    u16 flag;

    if ((func_080C95A8(13) && func_0809A9F0(context, unit)) ||
        func_080CDB54(unit) || func_080CDB6C(unit) ||
        func_080CD944(unit) || func_080C8260(unit))
        return 1;

    entry = func_080970E8(context, unit);
    if (entry) {
        if (!func_080C95A8(13))
            return 0;
        if (func_0809A9F0(context, entry->unit))
            return 1;
        return 0;
    }

    if (func_080C8240(unit) || func_080C8298(unit))
        flag = 6;
    else
        flag = 5;
    if (!func_080C95A8(flag))
        return 0;
    return 1;
}
