#include "ffta.h"

/* 0x0802DE58..0x0802DF10: 184 bytes. */
typedef struct {
    u8 identifier : 4;
    u8 unknown_00_high : 4;
} __attribute__((packed)) UnitSearchKey;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xDA];
    u8 identifier;
    u8 unknown_105[3];
} Unit;

extern Unit g_state_02000080[24];
extern Unit g_state_02002FC4[12];
extern u32 func_080C95A8(u32);
extern void *func_08096D7C(void);
extern Unit *func_0809A9C0(void *, int);

Unit *func_0802DE58(const UnitSearchKey *key)
{
    int i;
    Unit *unit;

    if ((u8)func_080C95A8(13) == 1) {
        for (i = 0; i < 2; i++) {
            unit = func_0809A9C0(func_08096D7C(), i);
            if (unit->identifier != 0xFF &&
                unit->identifier == key->identifier)
                return unit;
        }
    }
    unit = g_state_02000080;
    for (i = 0; i < 24; i++, unit++) {
        if (unit->identifier != 0xFF &&
            (unit->flags & 0x81) &&
            unit->identifier == key->identifier)
            return unit;
    }
    unit = g_state_02002FC4;
    for (i = 0; i < 12; i++, unit++) {
        if (unit->identifier != 0xFF &&
            (unit->flags & 1) &&
            unit->identifier == key->identifier)
            return unit;
    }
    return 0;
}
