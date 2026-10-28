#include "ffta.h"

typedef struct {
    u8 *objects[4];
    s16 handles[4];
} ObjectSlots0800C668;

extern ObjectSlots0800C668 data_02009148;
extern void *data_02009140;

void func_08000D90(s32 handle);
void func_08007170(void *owner, u8 *object);

void func_0800C668(u8 *object)
{
    s32 i;
    s32 handle;

    for (i = 0; i < 4; i++) {
        if (data_02009148.objects[i] == object) {
            handle = data_02009148.handles[i];
            if (handle != -1) {
                func_08000D90(handle);
                data_02009148.handles[i] = -1;
            }
            func_08007170(data_02009140, object);
            data_02009148.objects[i] = 0;
            return;
        }
    }
}
