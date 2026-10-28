#include "ffta.h"

/* 0x0802E338..0x0802E3E0: 168 bytes. */
typedef struct Unit Unit;

typedef struct {
    Unit *unit;
    u8 unknown_04[0x2C];
    u32 flags;
} Actor;

typedef struct {
    u8 unknown_0000[0x3C32];
    u8 count;
    u8 unknown_3C33;
    u16 entries[1];
} EventList;

typedef struct {
    u8 unknown_00[6];
    u8 value;
} Status;

extern EventList g_state_02000000;
extern Status *data_0200F444;
extern Actor *func_08096D88(void);
extern u8 func_080C9540(u32 event);
extern void *func_08096D7C(void);
extern s32 func_08099544(void *context);
extern u8 func_080C8240(Unit *unit);
extern u8 func_080C8260(Unit *unit);
extern s32 func_080970E8(void *context, Unit *unit);
extern u8 func_080CED5C(u32 value);

u8 func_0802E338(void)
{
    Actor *actor = func_08096D88();
    EventList *events;
    s32 index;

    if (!func_080C9540(0x207))
        return 0;

    index = 0;
    events = &g_state_02000000;
    for (; index < events->count; index++) {
        u16 entry = events->entries[index];
        if (entry == 0)
            continue;
        if (entry == 0x53)
            return 0;
    }

    if (!func_08099544(func_08096D7C()))
        return 0;
    if (func_080C8240(actor->unit))
        return 0;
    if (func_080C8260(actor->unit))
        return 0;
    if (actor->flags & 0x8000)
        return 0;
    if (func_080970E8(func_08096D7C(), actor->unit))
        return 0;
    if (func_080CED5C(1))
        return 0;
    return data_0200F444->value;
}
