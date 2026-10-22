#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 status;
    u8 unknown_05[0x13];
    u16 current;
    u16 maximum;
} ScriptThresholdObject;

void *func_08125578(u32 selector);
u8 func_080C8364(void *object);
u8 func_080C8348(void *object);

u32 func_08122984(u16 *context, const u8 *script)
{
    ScriptThresholdObject *object = func_08125578(script[1]);

    if (object != 0 && object->status != 0 &&
        !func_080C8364(object) && !func_080C8348(object)) {
        u8 threshold = script[2];
        u8 above = 0;

        if (threshold <= 9) {
            if (object->current > threshold)
                above = 1;
        } else if (object->current >
                   object->maximum * threshold / 100) {
            above = 1;
        }
        if (above)
            *context += script[3] | (script[4] << 8);
    }
    return 0x110;
}
