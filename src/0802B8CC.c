#include "ffta.h"

/* 0x0802B8CC..0x0802B8E8: 28 bytes. */
typedef struct {
    u8 unknown_00[0x15];
    u8 mode;
    u16 value;
} Payload0802B8CC;

extern void *func_08005BFC(void *task);

void func_0802B8CC(void *task, u8 mode, u16 value)
{
    Payload0802B8CC *payload = func_08005BFC(task);

    payload->mode = mode;
    payload->value = value;
}
