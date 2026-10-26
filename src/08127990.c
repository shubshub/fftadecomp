#include "ffta.h"

/* Target: complete [0x08127990, 0x08127A1A), 138 bytes including literal. */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Output08127990;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Output08127990 *output;
    s32 x;
    s32 y;
    u32 unknown_10;
    u8 selector;
    u8 unknown_15;
    u16 flags;
    u16 value;
} Descriptor08127990;

typedef struct {
    Output08127990 *output;
    void *object;
    s16 x;
    s16 y;
    u16 value;
    u8 flags;
} Payload08127990;

extern void *func_08125578(u8);
extern void *func_08096D7C(void);
extern void *func_08099560(void *, void *);
extern void func_08127458(Payload08127990 *);
extern u16 func_08127594(Payload08127990 *);
extern u16 func_081276D8(Payload08127990 *);

u32 func_08127990(void *task, Descriptor08127990 *descriptor,
                  Payload08127990 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        void *record;

        payload->output = descriptor->output;
        record = func_08125578(descriptor->selector);
        payload->object = func_08099560(func_08096D7C(), record);
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->flags = descriptor->flags;
        payload->value = descriptor->value;
        break;
    }
    case 1:
        break;
    case 0x100:
        func_08127458(payload);
        descriptor->phase = 0x101;
    case 0x101:
        descriptor->phase = func_08127594(payload);
        break;
    case 0x102:
        descriptor->phase = func_081276D8(payload);
        break;
    case 0x103:
        payload->output->complete = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
