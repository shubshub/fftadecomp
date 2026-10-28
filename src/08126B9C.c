#include "ffta.h"

struct Object08126B9C {
    u8 unknown_00[6];
    u8 field_06;
};

struct Descriptor08126B9C {
    u16 phase;
    u16 unknown_02;
    struct Object08126B9C *object;
};

struct Payload08126B9C {
    struct Object08126B9C *object;
};

extern u8 g_state_0200F390;
extern void func_08022CD4(u32 value, u32 mode);

/* Target: [0x08126B9C, 0x08126BFC), 96 bytes, 42 instructions. */
u32 func_08126B9C(void *task, struct Descriptor08126B9C *descriptor,
                  struct Payload08126B9C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->object = descriptor->object;
        func_08022CD4(16, 15);
        g_state_0200F390 = 15;
        break;
    case 1:
        break;
    case 0x100:
        if (g_state_0200F390 == 0)
            descriptor->phase = 0x102;
        break;
    case 0x102:
        payload->object->field_06 = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
