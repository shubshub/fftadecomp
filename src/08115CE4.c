#include "ffta.h"

/* Target: complete [0x08115CE4, 0x08115D72), 142 bytes including literal. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    const u8 *text;
    u8 *value;
} Descriptor08115CE4;

typedef struct {
    s16 x;
    s16 y;
    void *effect_task;
    u32 unknown_08;
    u8 *value;
    const u8 *text;
} Payload08115CE4;

extern void func_080D8C58(const u8 *, s16 *, s16 *);
extern void *func_08116480(u8, s16, s16, u8, u8, u16, u16, u8 *, void *);
extern void *func_081164E8(void *);

u32 func_08115CE4(void *task, Descriptor08115CE4 *descriptor,
                  Payload08115CE4 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->text = descriptor->text;
        payload->value = descriptor->value;
        *payload->value = 0;
        func_080D8C58(payload->text, &payload->x, &payload->y);
        payload->y -= 4;
        break;
    case 1:
        break;
    case 0x100:
        payload->effect_task = func_08116480(0, payload->x, payload->y, 6, 7,
                                            987, 986, payload->value, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->effect_task = func_081164E8(payload->effect_task);
        if (payload->effect_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
