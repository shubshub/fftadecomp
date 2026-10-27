#include "ffta.h"

extern void *func_080DD350(void *object);
extern u16 func_08099BF4(void *object);

/* 080DBD48..080DBD5A: 18 bytes, 7 instructions. */
u16 func_080DBD48(void *object)
{
    return func_08099BF4(func_080DD350(object));
}
