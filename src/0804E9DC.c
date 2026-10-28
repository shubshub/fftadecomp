#include "ffta.h"

/* 0x0804E9DC..0x0804E9EE: 18 bytes / 8 instructions. */
struct TaskPayload0804E9DC {
    u8 unknown_00[4];
    u16 flags;
};

extern struct TaskPayload0804E9DC *func_08005BFC(void *task);

void func_0804E9DC(void *task)
{
    struct TaskPayload0804E9DC *payload = func_08005BFC(task);

    payload->flags |= 1;
}
