#include "ffta.h"

typedef struct {
    u8 *container;
    u8 unknown_04[2];
    u16 count;
    u8 kind;
} TaskPayload;

void *func_08005BFC(void *task);

u32 func_08065060(void *task)
{
    TaskPayload *payload = func_08005BFC(task);
    u16 index = payload->count - 1;

    switch (payload->kind) {
    case 3: {
        void *source = ((void **)(payload->container + 0x424))[(s16)index];

        (*(void (**)(void *, void *, s32))0x0836D4BC)
            (payload->container + 0xA3C, source, 0x10);
        return (u32)(payload->container + 0xA3C);
    }
    case 4:
        return *(u16 *)((void **)(payload->container + 0x424))[(s16)index];
    case 5:
        return *(u8 *)((void **)(payload->container + 0x424))[(s16)index] | 0x10000;
    case 6:
        return *(u16 *)(payload->container + 0x424 + (s16)index * 4) | 0x20000;
    case 7: {
        void *source = ((void **)(payload->container + 0x424))[(s16)index];

        (*(void (**)(void *, void *, s32))0x0836D4BC)
            (payload->container + 0xA4C, source, 0x108);
        return (u32)(payload->container + 0xA4C);
    }
    default:
        return 0;
    }
}
