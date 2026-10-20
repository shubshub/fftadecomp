#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *data;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedObject;

void func_08131DD4(u8 *buffer, s32 index);
void func_080CDF30(void *object, u8 enabled);

void func_08132040(FlaggedObject *object)
{
    func_08131DD4((u8 *)object, 16);
    if (!(object->flags & 0x10))
        func_080CDF30(object->data, 1);
}
