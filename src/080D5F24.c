#include "ffta.h"

/* 0x080D5F24..0x080D5F72: 78 bytes. */
typedef struct EffectObject EffectObject;

extern u8 func_08010FF0(EffectObject *);
extern void func_08011428(EffectObject *);

u8 func_080D5F24(EffectObject **objects, u16 count)
{
    u8 finished = 1;
    u16 i;

    for (i = 0; i < count; i++) {
        if (objects[i] != 0) {
            if (func_08010FF0(objects[i])) {
                func_08011428(objects[i]);
                objects[i] = 0;
            } else {
                finished = 0;
            }
        }
    }
    return finished;
}
