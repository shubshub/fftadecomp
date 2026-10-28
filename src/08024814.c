#include "ffta.h"

/* 0x08024814..0x0802485E: 74 bytes / 32 instructions. */
struct Object08024814 {
    u8 unknown_00[4];
    u8 state;
    u8 unknown_05[2];
    u8 counter;
};

struct Input08024814 {
    u8 unknown_00[0x14];
    u16 buttons;
};

extern struct Input08024814 g_state_0200F390;
extern void func_08025174(struct Object08024814 *object);
extern void func_08024AD8(struct Object08024814 *object);

void func_08024814(struct Object08024814 *object)
{
    if (object->state == 0)
        return;

    if (object->state == 3) {
        func_08025174(object);
    } else if (object->state != 4) {
        if (g_state_0200F390.buttons & 0xF0) {
            object->state = 1;
            func_08024AD8(object);
        }
    }

    if (object->counter > 40)
        object->counter = 0;
    else
        ++object->counter;
}
