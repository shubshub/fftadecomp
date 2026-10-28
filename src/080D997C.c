#include "ffta.h"

/* 0x080D997C..0x080D99BE: 66 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
    u8 type;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern u8 *func_0800C614(void *resource);

u8 *func_080D997C(int index, u8 subindex)
{
    u8 *result = 0;
    ResourceObject *object = func_08005BFC(index);

    switch (object->type) {
    case 0:
        result = func_0800C614(object->resource);
        break;
    case 1:
        result = func_0800C614(object->resource) + subindex * 0x140;
        break;
    case 2:
        result = func_0800C614(object->resource) + subindex * 0x140;
        break;
    }
    return result;
}
