#include "ffta.h"

struct Parameters080DCAD4 {
    void *object;
    u8 kind;
    u8 interval;
    s16 value;
    u16 timer;
};

struct Command080DCAD4 {
    u16 state;
    u16 unknown_02;
    const struct Parameters080DCAD4 *parameters;
    u8 unknown_08[12];
    u16 flags;
};

struct Runtime080DCAD4 {
    void *object;
    u8 kind;
    u8 interval;
    s16 value;
    u16 timer;
    u16 flags;
};

extern void func_080DD248(void *object, s16 value);
extern void func_080DD288(void *object, s16 value);
extern void func_080DD304(void *object);
extern void func_080DD2C8(void *object);
extern void func_08141570(u32 mode, u16 id);
extern void func_08141520(u16 id);

/* Complete [0x080DCAD4, 0x080DCBBC): 232 bytes, 110 instructions. */
u32 func_080DCAD4(void *context, struct Command080DCAD4 *command,
                  struct Runtime080DCAD4 *runtime)
{
    switch (command->state) {
    case 0: {
        const struct Parameters080DCAD4 *parameters = command->parameters;

        runtime->object = parameters->object;
        runtime->kind = parameters->kind;
        runtime->value = parameters->value;
        runtime->timer = parameters->timer;
        runtime->interval = parameters->interval;
        runtime->flags = command->flags;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (runtime->timer != 0) {
            runtime->timer--;
            break;
        }
        switch (runtime->kind) {
        case 0:
            func_080DD248(runtime->object, runtime->value);
            break;
        case 1:
            func_080DD288(runtime->object, runtime->value);
            break;
        case 21: {
            u32 mode = 0;

            func_080DD304(runtime->object);
            if (runtime->flags & 1)
                break;
            if (runtime->flags & 2)
                mode = 1;
            else if (runtime->flags & 4)
                mode = 2;
            if (mode != 0)
                func_08141570(mode, 0x8D);
            else
                func_08141520(0x8D);
            break;
        }
        default:
            func_080DD2C8(runtime->object);
            break;
        }
        if (runtime->interval != 0) {
            runtime->timer = runtime->interval;
            command->state++;
        } else {
            command->state = 2;
        }
        break;
    case 0x101:
        runtime->timer--;
        if (runtime->timer == 0)
            command->state = 2;
        break;
    }
    return 0;
}
