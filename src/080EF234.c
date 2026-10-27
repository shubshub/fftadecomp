#include "ffta.h"

struct Command080EF234 {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 mode;
};

struct Runtime080EF234 {
    u8 mode;
    u8 unknown_01;
    u16 timer;
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_0A;
    void *object;
    void *resource;
    void *objects[2];
    u32 unknown_1C;
    void *operation;
    void *script;
};

extern const u8 data_084FA3B0[];
extern const u8 data_08399A54[];
extern const u8 data_08399A68[];

extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern u8 func_080DD73C(void *resource);
extern void *func_080D5E80(const void *data, u16 index, s16 x, s16 y,
                          s16 z, u16 value, u8 mode);
extern void func_08010884(void *object, u8 enabled);
extern void func_08011058(void *object, u8 enabled);
extern void *func_080DCFE4(void *object, const void *data, u32 first,
                          u32 second, u32 count, void *context, u32 value);
extern void *func_080DFD8C(const void *data, u32 first, u32 second,
                          u32 third, void *context);
extern u8 func_080D5F24(void **objects, u16 count);
extern void *func_080DBA5C(void *operation);

/* Complete [0x080EF234, 0x080EF37A): 326 bytes, 142 instructions. */
u32 func_080EF234(void *context, struct Command080EF234 *command,
                  struct Runtime080EF234 *runtime)
{
    switch (command->state) {
    case 0:
        runtime->mode = command->mode;
        runtime->object = command->object;
        runtime->resource = func_080DD748(runtime->object, &runtime->x,
                                         &runtime->y, &runtime->z);
        if (func_080DD73C(runtime->resource))
            runtime->y -= 8;
        break;
    case 0x100: {
        u32 count;
        u32 flags;

        runtime->objects[0] = func_080D5E80(data_084FA3B0, 0, runtime->x,
            runtime->y, runtime->z, 0x3FC, 6);
        func_08010884(runtime->objects[0], 1);
        count = (runtime->mode & 1) ? 4 : 2;
        runtime->operation = func_080DCFE4(runtime->object, data_08399A54,
                                           12, 44, count, context, 44);
        flags = (runtime->mode & 1) ? 16 : 8;
        runtime->script = func_080DFD8C(data_08399A68, 1, flags | 4, 0,
                                       context);
        runtime->timer = 10;
        command->state++;
        break;
    }
    case 0x101:
        runtime->timer--;
        if (runtime->timer == 0) {
            runtime->objects[1] = func_080D5E80(data_084FA3B0, 1, runtime->x,
                runtime->y, runtime->z, 0x3FC, 6);
            func_08011058(runtime->objects[1], 1);
            command->state++;
        }
        break;
    case 0x102:
        if (func_080D5F24(runtime->objects, 2)) {
            runtime->operation = func_080DBA5C(runtime->operation);
            if (runtime->operation == 0)
                command->state = 2;
        }
        break;
    }
    return 0;
}
