#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} ObjectState;

extern ObjectState *func_08005BFC(void *object);
extern void *func_0800C614(void *object);

void *func_080D9A14(void *object)
{
    return func_0800C614(func_08005BFC(object)->object);
}
