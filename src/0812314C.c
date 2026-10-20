#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} ScriptObject;

void *func_081255C8(u32 selector);
void func_0809A570(void *object, u32 clear, u32 set);

u32 func_0812314C(void *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);
    u32 clear = 0;
    u32 set = 0;
    u32 value = script[3];

    switch (script[2]) {
    case 0:
        if (value != 0)
            clear = 4;
        else
            set = 4;
        object->flags = (object->flags & ~clear) | set;
        break;
    case 1:
        if (value == 0) {
            clear = 0x1000;
            set = 0x4000;
        } else {
            clear = 0x5000;
            if (value != 1) {
                clear = 0x4000;
                set = 0x1000;
            }
        }
        func_0809A570(object, clear, set);
        break;
    }
    return 0x110;
}
