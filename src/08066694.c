#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *owner;
    u16 field_08;
    u16 field_0A;
    u16 field_0C;
    u16 unknown_0E;
    u8 flags;
    u8 unknown_11[3];
} Control08066694;

typedef struct {
    u8 unknown_000[0xA];
    u8 flags;
    u8 unknown_00B;
    u16 identifier;
    u8 unknown_00E[0xB9E];
    u32 value_0BAC;
} Root08066694;

typedef struct {
    Root08066694 *root;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[7];
    void *task;
    u8 unknown_14[0x5C];
    Control08066694 first;
    Control08066694 second;
    u8 unknown_98[0x32];
    u16 field_CA;
} Object08066694;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} TaskData08066694;

extern u16 func_08011860(void);
extern void func_08017D18(Control08066694 *control, u8 flags);
extern void func_08017E28(Control08066694 *control);
extern void func_08013390(u32 value);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void *func_08005BFC(void *task);

/* 0x08066694..0x08066718:
 * 70 B5 04 1C 26 1C 70 36 25 1C 84 35 21 1C CA 31
 * 00 20 08 80 AB F7 DA F8 00 04 00 28 01 D1 00 20
 * 27 E0 20 68 81 7A 30 1C B1 F7 2C FB 00 2D 06 D0
 * 29 7C BF 20 08 40 28 74 28 1C B1 F7 AB FB 20 68
 * 0D 49 40 18 00 68 AC F7 59 FE 20 68 81 89 0B 48
 * 81 42 03 D1 0A 48 01 21 62 F0 42 FF 20 7A 04 28
 * 06 D1 20 69 9F F7 80 FA 42 7A F7 21 11 40 41 72
 * 01 20 70 BC 02 BC 08 47 AC 0B 00 00 79 04 00 00
 * 81 05 00 00. */
u32 func_08066694(Object08066694 *object)
{
    Control08066694 *first = &object->first;
    Control08066694 *second = &object->second;

    object->field_CA = 0;
    if (func_08011860() == 0)
        return 0;

    func_08017D18(first, object->root->flags);
    if (second != 0) {
        second->flags &= 0xBF;
        func_08017E28(second);
    }
    func_08013390(object->root->value_0BAC);
    if (object->root->identifier == 0x479)
        func_080C9574(0x581, 1);
    if (object->mode == 4) {
        TaskData08066694 *data = func_08005BFC(object->task);

        data->flags &= 0xF7;
    }
    return 1;
}
