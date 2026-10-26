#include "ffta.h"

struct Command080E6A48 {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 mode;
};

struct Runtime080E6A48 {
    u8 mode;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    void *object;
    void *resource;
    u8 parameters[16];
    void *first;
    void *second;
    void *third;
};

struct Entry080E6A48 {
    u8 unknown_00[20];
};

extern const u8 data_0839756C[];
extern const struct Entry080E6A48 data_08397614[];
extern const u8 data_08397674[];

extern void *func_080DD748(void *object, s16 *x, s16 *y, u32 value);
extern void *func_080D6098(s16 x, s16 y, u32 first, u32 second,
                          u32 count, void *parameters, const void *data,
                          void *context);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern void *func_080D6134(void *operation);
extern void *func_080DBA5C(void *operation);

/* Complete [0x080E6A48, 0x080E6B0E): 198 bytes, 87 instructions. */
u32 func_080E6A48(void *context, struct Command080E6A48 *command,
                  struct Runtime080E6A48 *runtime)
{
    switch (command->state) {
    case 0: {
        u32 index;

        runtime->mode = command->mode;
        runtime->object = command->object;
        runtime->resource = func_080DD748(runtime->object, &runtime->x,
                                         &runtime->y, 0);
        runtime->first = func_080D6098(runtime->x, runtime->y, 0, 1, 4,
                                      runtime->parameters, data_0839756C,
                                      context);
        index = 0;
        if (runtime->mode == 1)
            index = 2;
        runtime->second = func_080DCFE4(runtime->object, &data_08397614[index],
                                       12, 0, 4, context, 0x37);
        runtime->third = func_080DFD8C(data_08397674, 1, 4, 0, context);
        break;
    }
    case 1:
        break;
    case 0x100:
        runtime->first = func_080D6134(runtime->first);
        if (runtime->first == 0) {
            runtime->second = func_080DBA5C(runtime->second);
            if (runtime->second == 0)
                command->state = 2;
        }
        break;
    }
    return 0;
}
