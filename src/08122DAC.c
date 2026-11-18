#include "ffta.h"

struct CommandState;
struct Object12638C;

extern void func_0812638C(struct Object12638C *object, void *value);

/* The scheduled task receives the whole four-byte command. */
u32 func_08122DAC(struct CommandState *state, const u8 *command)
{
    func_0812638C((struct Object12638C *)state, (void *)command);
    return 0x115;
}
