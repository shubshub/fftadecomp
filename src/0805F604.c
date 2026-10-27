#include "ffta.h"

/* 0x0805F604..0x0805F670: 108 bytes. */
typedef struct {
    u8 unknown_00[2];
    u8 active;
} ObjectStatus;

typedef struct {
    u8 unknown_00[8];
    void *objects[2];
    u8 fallback[2];
} StatusGroup;

extern StatusGroup *data_0200F44C;
extern ObjectStatus *func_08005BFC(void *object);

s32 func_0805F604(void)
{
    s32 active = 0;
    s32 fallback = 0;
    s32 occupied = 0;
    s32 index;

    for (index = 0; index < 2; index++) {
        StatusGroup *group = data_0200F44C;
        if (group->objects[index] != 0) {
            if (func_08005BFC(group->objects[index])->active != 0)
                active++;
            occupied++;
        } else {
            fallback += group->fallback[index];
        }
    }

    if (fallback != 0) {
        if (occupied == 0)
            return 1;
        return active != 0;
    }
    if (occupied == 2)
        return active == 2;
    return active;
}
