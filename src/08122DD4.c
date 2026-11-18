#include "ffta.h"

struct CommandState;
struct Object1263B0;

extern void func_081263B0(struct Object1263B0 *object, u8 value);

u32 func_08122DD4(struct CommandState *state, const u8 *command)
{
    func_081263B0((struct Object1263B0 *)state, command[1]);
    return 0x115;
}
