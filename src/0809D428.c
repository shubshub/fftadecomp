#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 phase;
} Status0809D428;

typedef struct {
    u8 unknown_00[0xDC];
    Status0809D428 status;
    u8 unknown_E0[0x44];
} Object0809D428;

typedef void (*BufferInitializer0809D428)(void *destination, u32 size);

extern BufferInitializer0809D428 const g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);

/* Complete [0x0809D428, 0x0809D458): 48 bytes, 19 instructions. */
Object0809D428 *func_0809D428(void)
{
    Object0809D428 *object = func_08022840(sizeof(*object));
    Status0809D428 *status;

    g_callbacks_0836D4B8[0](object, sizeof(*object));
    status = &object->status;
    status->phase = 0;
    return object;
}
