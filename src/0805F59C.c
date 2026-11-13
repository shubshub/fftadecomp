#include "ffta.h"

// 0x0805F59C..0x0805F604: 104 bytes, 44 instructions.
// f0b5474680b40006070e0904090c884600260025002400e00134012c0edc10480068a100
// 083040180568002df4d0281ca6f716fb061c3078b842edd1022c09d0281ca6f7e5fa3081
// 404670810549281ca6f7dcfa08bc9846f0bc01bc004700004cf400020b010000

typedef struct {
    u8 kind;
    u8 unknown_01[7];
    u16 state_08;
    u16 value_0a;
} Payload0805F59C;

typedef struct {
    u8 unknown_00[8];
    void *tasks[2];
} Context0805F59C;

extern Context0805F59C *data_0200F44C;

extern Payload0805F59C *func_08005BFC(void *task);
extern u16 func_08005BAC(void *task);
extern void func_08005BA8(void *task, u16 state);

void func_0805F59C(u8 kind, u16 value)
{
    Payload0805F59C *payload = 0;
    void *task = 0;
    s32 i;

    for (i = 0; i <= 1; i++) {
        task = data_0200F44C->tasks[i];
        if (task == 0)
            continue;
        payload = func_08005BFC(task);
        if (payload->kind == kind)
            break;
    }

    if (i != 2) {
        payload->state_08 = func_08005BAC(task);
        payload->value_0a = value;
        func_08005BA8(task, 0x10B);
    }
}
