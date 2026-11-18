#include "ffta.h"

/* 0x080D9BA8..0x080D9BC0: 24 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 attributes;
} Attributes0800C628;

typedef struct {
    u8 unknown_00[4];
    Attributes0800C628 *object;
} ScanlineTaskPayload;

extern void *func_08005BFC(void *task);
extern void func_0800C628(Attributes0800C628 *object, u8 enabled);

void func_080D9BA8(void *task, u8 enabled)
{
    ScanlineTaskPayload *payload = func_08005BFC(task);

    func_0800C628(payload->object, enabled);
}
