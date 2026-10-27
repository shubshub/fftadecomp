#include "ffta.h"

/* 0x0800C6CC - 64 bytes. Initialize the object slots and their owner. */
typedef struct {
    u8 *objects[4];
    s16 handles[4];
} ObjectSlots0800C6CC;

extern ObjectSlots0800C6CC data_02009148;
extern void *data_02009140;
void func_080105B8(void);

void func_0800C6CC(void *owner)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        data_02009148.objects[i] = 0;
        data_02009148.handles[i] = -1;
    }
    data_02009140 = owner;
    func_080105B8();
}
