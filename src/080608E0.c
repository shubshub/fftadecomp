#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
    u8 unknown_11[3];
} Effect080608E0;

typedef struct {
    u8 unknown_0000[0x5C];
    Effect080608E0 primary;
    Effect080608E0 secondary;
} Object080608E0;

typedef struct {
    u8 unknown_0000[0x1D];
    u8 flags;
    u16 identifier;
    u8 unknown_0020[0x590];
    u32 value_05B0;
} Global080608E0;

extern Global080608E0 *data_0200F44C;
extern u16 func_08011860(Object080608E0 *object);
extern void func_08017D18(Effect080608E0 *effect, u8 mask);
extern void func_08017E28(Effect080608E0 *effect);
extern void func_08013390(u32 value);
extern void func_080C9574(u16 bitIndex, u16 enabled);

/* 080608E0..0806094C: 108 bytes, 42 reachable instructions. */
u32 func_080608E0(Object080608E0 *object)
{
    Effect080608E0 *primary = &object->primary;
    Effect080608E0 *secondary = &object->secondary;

    if (func_08011860(object) == 0)
        return 0;

    func_08017D18(primary, data_0200F44C->flags);
    if (secondary != 0) {
        secondary->flags &= 0xBF;
        func_08017E28(secondary);
    }
    func_08013390(data_0200F44C->value_05B0);
    if (data_0200F44C->identifier == 0x479)
        func_080C9574(0x581, 1);
    return 1;
}
