#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} DrawingState;

extern DrawingState *func_08005BFC(void *object);
extern void *func_0800C614(void *object);
extern void func_080DA3B8(s16 x, s16 y, s16 width, s16 height, void *buffer);
extern void func_080DA598(s16 x, s16 y, s16 width, s16 height, void *buffer);

void func_080DABC4(void *object, u16 x, u16 y, u16 width, u16 height, u8 mode)
{
    void *buffer = func_0800C614(func_08005BFC(object)->object);

    if (mode == 0)
        func_080DA3B8((s16)x, (s16)y, (s16)width, (s16)height, buffer);
    else
        func_080DA598((s16)x, (s16)y, (s16)width, (s16)height, buffer);
}
