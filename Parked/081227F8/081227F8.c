#include "ffta.h"

typedef struct {
    u8 *data;
} ScriptObject;

typedef struct {
    u32 unknown_00;
    u16 result;
} ScriptContext;

ScriptObject *func_081255C8(u32 selector);
u8 func_0801CC18(u8 x, u8 y);
void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                  s16 *screen_y, s16 *depth);
u16 func_0801BA20(s16 x, s16 y, u16 value);
u16 func_0801BB0C(s16 x, s16 y, u16 value);
void func_08128898(ScriptContext *context, u16 x, u16 y, u8 value);
extern const u8 g_table_083A8190[];

u32 func_081227F8(ScriptContext *context, const u8 *script)
{
    ScriptObject *object = func_081255C8(script[1]);
    s16 x;
    s16 y;
    s16 z;
    u16 screen_x;
    u16 screen_y;

    x = object->data[0xF6] * 32 + 16;
    z = object->data[0xF7] * 32 + 16;
    y = func_0801CC18(object->data[0xF6], object->data[0xF7]) * 16;
    func_0801C918(x, y, z, &x, &y, &z);
    screen_x = x - 120;
    screen_y = y - 100;
    switch (script[2]) {
    case 1:
        context->result = func_0801BB0C(screen_x, screen_y, script[3]);
        break;
    case 2:
        context->result = func_0801BA20(screen_x, screen_y, script[3]);
        break;
    case 0:
        context->result = func_0801BA20(screen_x, screen_y,
                                       g_table_083A8190[script[3] - 1]);
        break;
    case 3:
        func_08128898(context, screen_x, screen_y, script[3]);
        return 0x115;
    }
    return 0x114;
}
