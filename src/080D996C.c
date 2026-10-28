#include "ffta.h"

/* 0x080D996C..0x080D997C: 16 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern u8 *func_0800C614(void *resource);

u8 *func_080D996C(int index)
{
    return func_0800C614(func_08005BFC(index)->resource);
}
