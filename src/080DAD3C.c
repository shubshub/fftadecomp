#include "ffta.h"

/* 0x080DAD3C..0x080DAD74: 56 bytes. */
typedef struct {
    u32 unknown_00;
    void *object;
} Payload080DAD3C;

extern void *func_08005BFC(void *task);
extern void *func_0800C614(const void *object);
extern void func_080DA1C4(s16 x, s16 y, u16 value, void *data);

void func_080DAD3C(void *task, u16 x, u16 y, u16 value)
{
    Payload080DAD3C *payload = func_08005BFC(task);
    void *data = func_0800C614(payload->object);

    func_080DA1C4((s16)x, (s16)y, value, data);
}
