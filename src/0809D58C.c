#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 phase;
} Status0809D58C;

typedef struct {
    void *child;
    u8 unknown_04[0x16];
    u16 unknown_1A;
    u16 current;
    u16 initial;
    u8 unknown_20[7];
    s8 value;
    u8 mode;
    u8 unknown_29[0xB3];
    Status0809D58C status;
} Object0809D58C;

extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_0809A530(void *child, u32 value);
extern void func_0809A570(void *child, u32 clear, u32 set);

/* 0x0809D58C..0x0809D5E8: 92 bytes, 43 instructions. */
void func_0809D58C(Object0809D58C *object)
{
    Status0809D58C *status = &object->status;

    status->phase = 0;
    status->unknown_00 = 0;
    object->unknown_1A = 0;
    object->current = object->initial;
    func_0809836C(object->child, 11, object->value, 0);
    switch (object->mode) {
    case 0:
    case 1:
        object->mode = 1;
        break;
    case 2:
    case 3:
        object->mode = 3;
        break;
    }
    func_0809A530(object->child, object->mode);
    func_0809A570(object->child, 0, 0x100);
}
