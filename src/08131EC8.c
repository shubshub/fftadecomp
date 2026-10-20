#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *data;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedObject;

void func_08131DD4(u8 *buffer, s32 index);
void func_080CDD88(void *object, u8 enabled);

void func_08131EC8(FlaggedObject *object)
{
    func_08131DD4((u8 *)object, 4);
    if (!(object->flags & 0x10))
        func_080CDD88(object->data, 1);
}
