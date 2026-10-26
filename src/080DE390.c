#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    s8 value;
} ObjectState;

extern void func_0809836C(ObjectState *object, u32 mode, s8 value, u32 option);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_0809A530(void *object, u32 value);

void func_080DE390(ObjectState *object)
{
    func_0809836C(object, 1, object->value, 0);
    func_0809A570(object, 0, 0x100);
    func_0809A530(object, 1);
}
