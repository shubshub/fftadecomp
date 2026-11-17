#include "ffta.h"

/* Complete [0x08123398, 0x081233F8): 96 bytes, 42 instructions and the
 * literal words 0xFFFFFF00 and 0x00000115.  The eight-byte argument record
 * is built on the stack, its coordinates are resolved in place by
 * func_08124E74 (&x in r3, &y in the outgoing stack word), and it is passed
 * by value in r1/r2 to func_08127B80, as func_08123320 does. */

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s16 x;
    s16 y;
    u16 value;
} ScriptArguments;

void func_08124E74(u8 selector, s8 x, s8 y, s16 *out_x, s16 *out_y);
void func_08127B80(void *context, ScriptArguments arguments);

u32 func_08123398(void *context, const u8 *script)
{
    ScriptArguments arguments;

    arguments.selector = script[1];
    func_08124E74(arguments.selector, (s8)script[2], (s8)script[3],
                  &arguments.x, &arguments.y);
    arguments.mode = script[4];
    arguments.value = script[5] | (script[6] << 8);
    func_08127B80(context, arguments);
    return 0x115;
}
