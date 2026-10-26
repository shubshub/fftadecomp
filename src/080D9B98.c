#include "ffta.h"

/* 0x080D9B98..0x080D9BA8: 16 bytes. */
typedef struct {
    u8 unknown_00[4];
    void *resource;
} ResourceObject;

extern ResourceObject *func_08005BFC(int index);
extern void func_0800C64C(void *resource);

void func_080D9B98(int index)
{
    func_0800C64C(func_08005BFC(index)->resource);
}
