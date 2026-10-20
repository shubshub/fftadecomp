#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 value_14;
    u16 value_16;
} ControlState08096E78;

void func_08148830(void);
u32 func_08092784(void *object, u16 first, u16 second);
void func_080BD06C(void);
void func_080A94D4(void);
void func_0809A3F4(void *context);
void func_08024814(void *view);

void func_08096E78(u8 index, u8 *flag)
{
    switch (*flag) {
    case 0:
        *flag = 1;
        break;
    case 1: {
        void *object;
        void *context;

        func_08148830();
        object = *(void **)0x0200F4A8;
        if (object != 0) {
            ControlState08096E78 *state = (ControlState08096E78 *)0x0200F390;

            func_08092784(object, state->value_16, state->value_14);
        }
        func_080BD06C();
        func_080A94D4();
        context = *(void **)0x0200F4B0;
        if (context != 0)
            func_0809A3F4(context);
        func_08024814((void *)0x0200F3AC);
        break;
    }
    }
}
