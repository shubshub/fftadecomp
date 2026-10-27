#include "ffta.h"

struct DmaRequest08000D08 {
    const void *source;
    void *destination;
    u32 control;
    u8 state;
    u8 flags;
    u16 unknown_0E;
};

struct DmaRegisters08000D08 {
    const void *source;
    void *destination;
    u32 control;
};

extern struct DmaRequest08000D08 data_03002C10[4];
extern u16 data_03002BC0[4];
extern struct DmaRegisters08000D08 *const data_0836D470[4];
extern void func_08003A08(u32 channel);

void func_08000D08(void)
{
    struct DmaRequest08000D08 *request = data_03002C10;
    u16 *busy;
    struct DmaRegisters08000D08 *const *registers;
    s32 channel;

    for (channel = 0, busy = data_03002BC0, registers = data_0836D470;
         channel < 4; busy++, registers++, channel++, request++) {
        if (*busy == 0 && request->state == 3) {
            (*registers)->control = 0;
            func_08003A08(channel);
        }
    }
}
