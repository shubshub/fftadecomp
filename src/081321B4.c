#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *data;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedObject;

extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CE148(void *object, u8 enabled);
extern void func_080CE470(void *object, u8 mode);

void func_081321B4(FlaggedObject *object)
{
    if (func_080CD8FC(object->data))
    {
        func_080CDD88(object->data, 0);
        object->flags |= 0x100;
    }
    else
    {
        func_08131DD4((u8 *)object, 30);
        if (!(object->flags & 0x10))
        {
            func_080CE148(object->data, 1);
            func_080CE470(object->data, 3);
        }
    }
}
