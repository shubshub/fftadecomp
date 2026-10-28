#include "ffta.h"

typedef struct Unit080CA268 {
    u8 unknown_00[0x2A];
    u16 equipment[5];
} Unit080CA268;

typedef struct EquipmentSet080CA268 {
    u8 unknown_00[8];
    u16 equipment[5];
} EquipmentSet080CA268;

typedef void (*EquipmentCopy080CA268)(void *destination,
                                     const void *source, u32 size);

extern EquipmentCopy080CA268 const data_0836D4BC;
extern u8 func_080C8240(const Unit080CA268 *unit);
extern u8 func_080C8260(const Unit080CA268 *unit);
extern s32 func_080C7EA4(const void *unit, u32 field);
extern u8 func_080C8194(const void *unit, u8 category);
extern s32 func_080CA900(u16 item, u8 quantity);
extern void func_080CAB24(u16 item, u8 quantity);
extern void func_080CCF44(Unit080CA268 *unit, u16 item);

/* Complete [0x080CA268, 0x080CA2E8): 128 bytes, 53 instructions. */
void func_080CA268(Unit080CA268 *unit, const EquipmentSet080CA268 *source)
{
    int register_items = 1;
    u16 *item;
    int remaining;

    data_0836D4BC(unit->equipment, source->equipment,
                  sizeof(unit->equipment));
    if (func_080C8240(unit) || func_080C8260(unit))
        register_items = 0;
    if (func_080C7EA4(unit, 3) == 23 && !func_080C8194(unit, 94))
        register_items = 0;

    for (item = unit->equipment, remaining = 4;
         remaining >= 0; item++, remaining--) {
        if (register_items) {
            func_080CA900(*item, 1);
            func_080CAB24(*item, 1);
        }
        func_080CCF44(unit, *item);
    }
}
