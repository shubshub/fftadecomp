#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    void *data;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedObject;

u8 func_080CD8FC(const void *object);
void func_080CDD88(void *object, u8 enabled);
void func_080CDE14(void *object, u8 enabled);
void func_08131DD4(u8 *buffer, s32 index);

void func_08131EF0(FlaggedObject *object)
{
    if (func_080CD8FC(object->data)) {
        if (!(object->flags & 0x10)) {
            func_080CDD88(object->data, 0);
            object->flags |= 0x100;
        }
    } else {
        func_08131DD4((u8 *)object, 8);
        if (!(object->flags & 0x10))
            func_080CDE14(object->data, 1);
    }
}
