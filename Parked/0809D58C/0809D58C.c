#include "ffta.h"

typedef struct {
    void *child;
    u8 unknown_04[0x16];
    u16 counter;
    u16 current;
    u16 initial;
    u8 unknown_20[7];
    s8 value;
    u8 mode;
    u8 unknown_29[0xB3];
    u16 coordinates[2];
} Object0809D58C;

extern void func_0809836C(void *child, u16 identifier, s8 value, u8 mode);
extern void func_0809A530(void *child, u32 value);
extern void func_0809A570(void *child, u32 clear, u32 set);

/* 0x0809D58C..0x0809D5E8: 92 bytes, 43 instructions. */
void func_0809D58C(Object0809D58C *object)
{
    u16 *coordinates = object->coordinates;

    coordinates[1] = 0;
    coordinates[0] = 0;
    object->counter = 0;
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
