#include "ffta.h"

/* 0x08124CE8..0x08124D58: 112 bytes. */
typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0xF3];
    u8 field_f8;
    u8 unknown_f9[0x0F];
} UnitRecord;

typedef struct {
    u8 unknown_00[0xF6];
    u8 first;
    u8 second;
    u8 unknown_f8;
    u8 saved_first;
    u8 saved_second;
} ObjectData;

typedef struct {
    ObjectData *data;
} UnitObject;

typedef struct {
    u32 unknown_00;
    UnitRecord *unit;
} QueueEntry;

extern UnitRecord g_state_02002FC4[];
extern void *func_08096D7C(void);
extern UnitObject *func_08092440(void *context, UnitRecord *unit);
extern void func_08124710(UnitObject *object, u32 mode, u8 value);
extern u8 func_080C8240(UnitRecord *unit);
extern QueueEntry *func_08121C70(u8 index);

void func_08124CE8(void)
{
    UnitRecord *unit = g_state_02002FC4;
    s32 next = 0;
    s32 remaining;

    for (remaining = 11; remaining >= 0; remaining--, unit++) {
        if (unit->active) {
            UnitObject *object = func_08092440(func_08096D7C(), unit);
            object->data->saved_first = object->data->first;
            object->data->saved_second = object->data->second;
            func_08124710(object, 1, unit->field_f8);
            if (func_080C8240(unit))
                func_08121C70(next++ - 128)->unit = unit;
        }
    }
}
