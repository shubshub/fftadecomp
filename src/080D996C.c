#include "ffta.h"

/* 0x080D996C..0x080D997C: 16 bytes. */
struct Object0800C614;

typedef struct {
    u8 unknown_00[4];
    struct Object0800C614 *resource;
} ScrollTaskPayload;

extern void *func_08005BFC(void *task);
extern void *func_0800C614(const struct Object0800C614 *object);

u16 *func_080D996C(void *task)
{
    ScrollTaskPayload *payload = func_08005BFC(task);

    return func_0800C614(payload->resource);
}
