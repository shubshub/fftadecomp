#include "ffta.h"

typedef struct {
    u8 unknown_000[0xA0];
    void *primary;
    u8 unknown_0A4[0xB4];
    void *objects[4];
} ObjectGroup;

extern ObjectGroup g_state_02007F40;
extern void func_08020F80(void *object, u8 mode);

/* 0801AD60..0801ADA4: 68 bytes. */
void func_0801AD60(u8 mode)
{
    ObjectGroup *group = &g_state_02007F40;
    void **objects;
    u8 index;

    if (group->primary != 0)
        func_08020F80(group->primary, mode);

    index = 0;
    objects = group->objects;
    do {
        if (objects[index] != 0)
            func_08020F80(objects[index], mode);
        index++;
    } while (index < 4);
}
