#include "ffta.h"

/* 0x0801ADA4..0x0801ADE0: 60 bytes. */
typedef struct {
    u8 unknown_00[0xA0];
    u8 *primary;
    u8 unknown_A4[0xB4];
    u8 *objects[4];
} ObjectGroup;

extern ObjectGroup g_state_02007F40;
extern void func_08020F64(u8 *object);

void func_0801ADA4(void)
{
    ObjectGroup *group = &g_state_02007F40;
    u8 **objects;
    u8 index;

    if (group->primary != 0) {
        func_08020F64(group->primary);
    }
    index = 0;
    objects = group->objects;
    do {
        if (objects[index] != 0) {
            func_08020F64(objects[index]);
        }
        index++;
    } while (index < 4);
}
