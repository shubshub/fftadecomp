#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} ScriptData;

typedef struct {
    ScriptData *data;
} ScriptObject;

void *func_081255C8(u32 selector);
void func_08124974(u8 start_x, u8 start_y, u8 end_x, u8 end_y, u8 value);

u32 func_081234B4(void *context, const u8 *script)
{
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    ScriptObject *object = func_081255C8(script[1]);

    start_x = object->data->x;
    start_y = object->data->y;
    end_x = script[2] & 0xF;
    end_y = (script[2] & 0xF0) >> 4;

    if (start_x == end_x || start_y == end_y)
        func_08124974(start_x, start_y, end_x, end_y, script[3]);
    return 0x110;
}
