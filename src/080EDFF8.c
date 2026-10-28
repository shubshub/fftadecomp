#include "ffta.h"

struct Command080EDFF8 {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 mode;
};

struct Runtime080EDFF8 {
    u16 timer;
    s16 x;
    s16 y;
    u8 mode;
    u8 unknown_07;
    void *resource;
    void *object;
    u32 parameters[3];
    void *movement;
    void *first;
    void *second;
    void *operation;
    void *script;
};

extern const u8 data_083995B8[];
extern const u8 data_088F4F80[];
extern const u8 data_089497C0[];
extern const u8 data_0894D69C[];
extern const u8 data_08399600[];
extern const u8 data_08399614[];

extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void func_080D7220(const void *data, u32 first, u32 second,
                          s16 x, s16 y, u32 value);
extern void *func_080D4704(const void *data, void *context);
extern void *func_080D3E9C(const void *data, void *context);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void *func_080D3F08(void *operation);
extern void *func_080D4774(void *operation);
extern void *func_080D6134(void *operation);
extern void *func_080DBA5C(void *operation);

/* Complete [0x080EDFF8, 0x080EE13C): 324 bytes, 135 instructions. */
u32 func_080EDFF8(void *context, struct Command080EDFF8 *command,
                  struct Runtime080EDFF8 *runtime)
{
    switch (command->state) {
    case 0:
        runtime->object = command->object;
        runtime->mode = command->mode;
        runtime->resource = func_080DD748(runtime->object, &runtime->x,
                                         &runtime->y, 0);
        break;
    case 0x100: {
        u32 count;
        u32 flags;

        runtime->movement = func_080D6098(runtime->x, runtime->y, 0, 1, 3,
            runtime->parameters, data_083995B8, context);
        func_080D7220(data_088F4F80, 0, 2, runtime->x, runtime->y, 0);
        runtime->second = func_080D4704(data_089497C0, context);
        runtime->first = func_080D3E9C(data_0894D69C, context);
        count = (runtime->mode & 1) ? 2 : 4;
        runtime->operation = func_080DCFE4(runtime->object, data_08399600,
                                           12, 42, count, context, 42);
        flags = (runtime->mode & 1) ? 8 : 16;
        runtime->script = func_080DFD8C(data_08399614, 1, flags | 4, 0,
                                       context);
        runtime->timer = 12;
        command->state++;
        break;
    }
    case 0x101:
        runtime->first = func_080D3F08(runtime->first);
        if (runtime->first != 0)
            break;
        runtime->second = func_080D4774(runtime->second);
        if (runtime->second != 0)
            break;
        runtime->movement = func_080D6134(runtime->movement);
        if (runtime->movement == 0)
            command->state++;
        break;
    case 0x102:
        runtime->operation = func_080DBA5C(runtime->operation);
        if (runtime->operation == 0)
            command->state = 2;
        break;
    }
    return 0;
}
