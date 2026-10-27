#include "ffta.h"

/* 0805F4D8..0805F540: 104 bytes. */
struct ObjectData {
    u8 id;
    u8 unknown_01;
    u8 state;
};

struct ObjectList {
    u8 unknown_00[8];
    void *objects[2];
};

extern struct ObjectList *data_0200F44C;
extern struct ObjectData *func_08005BFC(void *object);

void func_0805F4D8(u8 id, u8 mode)
{
    struct ObjectData *record = 0;
    u8 state;

    if (id == 0) {
        if (data_0200F44C->objects[0] == 0)
            return;
        record = func_08005BFC(data_0200F44C->objects[0]);
    } else {
        s32 i;

        for (i = 0; i < 2; i++) {
            if (data_0200F44C->objects[i] == 0)
                continue;
            record = func_08005BFC(data_0200F44C->objects[i]);
            if (record->id == id)
                break;
        }
        if (i == 2)
            return;
    }
    state = 2;
    if (mode != 0)
        state = 6;
    record->state = state;
}
