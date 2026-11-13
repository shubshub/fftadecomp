#include "ffta.h"

// func_081247B4: 0x081247B4..0x0812484E, 154 bytes, 77 instructions.

typedef struct {
    void *record;
    u8 unknown_04[0x1B];
    s8 layer;
} SceneObject;

extern void *func_08096D7C(void);
extern s32 func_08099CDC(void *context, SceneObject **objects);
extern u8 func_080C8240(void *record);
extern u8 func_080C8260(void *record);
extern u8 func_080C8298(void *record);
extern void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);

void func_081247B4(u8 mode)
{
    SceneObject *objects[13];
    s32 count = func_08099CDC(func_08096D7C(), objects);
    s32 i;

    for (i = 0; i < count; i++) {
        SceneObject *object = objects[i];

        switch (mode) {
        case 0:
            if (!func_080C8240(object->record) && !func_080C8260(object->record) &&
                !func_080C8298(object->record))
                func_0809836C(object, 10, object->layer, 0);
            break;
        case 1:
            if (func_080C8240(object->record))
                func_0809836C(object, 10, object->layer, 0);
            break;
        case 2:
            if (func_080C8260(object->record))
                func_0809836C(object, 10, object->layer, 0);
            break;
        default:
            func_0809836C(object, 10, object->layer, 0);
            break;
        }
    }
}
