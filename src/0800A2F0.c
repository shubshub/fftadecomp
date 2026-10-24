#include "ffta.h"

/* 0x0800A2F0 - 64 bytes including the literal pool.
 * Target: 70b5061c0d1c68781bf13ef9041c002c11d08cf041fd0068a0420cd1074940180078
 *         a978884206d1e97828790002014370880918718070bc01bc004701010000
 */
typedef struct {
    u16 unknown_00;
    u16 position;
} ScriptContext0800A2F0;

typedef struct {
    u8 unknown_000[0x101];
    u8 state;
} ScriptObject0800A2F0;

typedef struct {
    ScriptObject0800A2F0 *object;
} ActiveObject0800A2F0;

void *func_08125578(u8 selector);
ActiveObject0800A2F0 *func_08096D88(void);

void func_0800A2F0(ScriptContext0800A2F0 *context, const u8 *instruction)
{
    ScriptObject0800A2F0 *object = func_08125578(instruction[1]);

    if (object != 0 && func_08096D88()->object == object &&
        object->state == instruction[2])
        context->position += instruction[3] | (instruction[4] << 8);
}
