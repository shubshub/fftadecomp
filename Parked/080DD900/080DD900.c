#include "ffta.h"

/* 0x080DD900 - 170 bytes; following alignment is outside the function.
 * Target: 30b50c1c131c2288012a4ad0012a02dc002a08d045e08020400082421ed00130
 *         824236d03de061680c681c6008791871487958710006001601256d42a84201d1
 *         e07f5871c888d8800889188100040014a84200d11a814889588122e058890028
 *         02d0013858811ce01879002806d11868d98805229a5600f0d9fb07e01868d988
 *         1a895b791b061b1600f0eefb2088013006e0186800f02cfc0006002801d00220
 *         2080002030bc02bc0847
 */
typedef struct {
    u8 unknown_00[0x1F];
    s8 field_1f;
} Object080DD900;

typedef struct {
    Object080DD900 *object;
    u8 kind;
    s8 value;
    u16 action;
    s16 option;
    u16 delay;
} Parameters080DD900;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    const Parameters080DD900 *parameters;
} Descriptor080DD900;

extern void func_080DE12C(void *object, u16 action, s8 value);
extern void func_080DE168(void *object, u16 action, u16 option, s8 value);
extern u8 func_080DE1F0(void *object);

u32 func_080DD900(void *task, void *descriptor, void *payload)
{
    Descriptor080DD900 *state = descriptor;
    Parameters080DD900 *data = payload;
    const Parameters080DD900 *parameters;

    (void)task;
    switch (state->state) {
    case 0:
        parameters = state->parameters;
        data->object = parameters->object;
        data->kind = parameters->kind;
        data->value = parameters->value;
        if (data->value == -1)
            data->value = data->object->field_1f;
        data->action = parameters->action;
        data->option = parameters->option;
        if (data->option == -1)
            data->option = 0;
        data->delay = parameters->delay;
        break;
    case 1:
        break;
    case 0x100:
        if (data->delay != 0) {
            data->delay--;
        } else {
            if (data->kind == 0)
                func_080DE12C(data->object, data->action, data->value);
            else
                func_080DE168(data->object, data->action, data->option, data->value);
            state->state++;
        }
        break;
    case 0x101:
        if (func_080DE1F0(data->object))
            state->state = 2;
        break;
    }
    return 0;
}
