#include "ffta.h"

extern void func_080A0468(void *object, s16 first, s16 second,
                          s16 third, s16 fourth);

/* 0x080A7FC4..0x080A7FE8: 36 bytes. */
void func_080A7FC4(void *object, s16 first, s16 second,
                   s16 third, s16 fourth)
{
    func_080A0468(object, first, second, third, fourth);
}
