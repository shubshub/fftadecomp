#include "ffta.h"

// Target: complete [0x08111D50, 0x08111DE8), 152 bytes: 71 instructions
// (148 code bytes) and one literal word.

struct Actor {
    Struct08011040 *object;
};

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    struct Actor *actor;
};

struct Payload {
    u16 counter;
    u16 unknown_02;
    u32 unknown_04;
    struct Actor *actor;
};

extern void func_080107D4(void *object, s16 x, s16 y, s16 z);

u32 func_08111D50(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u16 x;
    u16 y;
    u16 z;

    switch (descriptor->phase) {
    case 0:
        payload->actor = descriptor->actor;
        break;
    case 1:
        break;
    case 0x100: {
        u16 offsets[5] = {4, 2, 1, 0, 1};

        func_08011040(payload->actor->object, &x, &y, &z);
        y -= offsets[payload->counter];
        func_080107D4(payload->actor->object, x, y, z);
        if (++payload->counter > 4)
            descriptor->phase = 2;
        break;
    }
    }
    return 0;
}
