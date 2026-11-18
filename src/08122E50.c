#include "ffta.h"

struct CommandState;

extern void func_08121BDC(u8 mode);
extern void func_08124F24(void);
extern void func_080A9528(void);

u32 func_08122E50(struct CommandState *state, const u8 *command)
{
    func_08121BDC(command[1]);
    switch (command[1]) {
    case 8:
        func_080A9528();
        break;
    case 4:
        func_08124F24();
        break;
    }
    return 0x11D;
}
