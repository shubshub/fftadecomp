#include "ffta.h"

struct CommandState;
struct Object12640C;

extern void func_0812640C(struct Object12640C *object);

u32 func_08122E1C(struct CommandState *state, const u8 *command)
{
    func_0812640C((struct Object12640C *)state);
    return 0x115;
}
