#include "ffta.h"

typedef struct Owner0809D86C Owner0809D86C;

typedef struct {
    Owner0809D86C *owner;
    u16 x;
    u16 y;
    u16 value;
    s8 dx;
    s8 dy;
    u8 unknown_0C[0x58];
} Object0809D86C;

typedef void (*BufferInitializer0809D86C)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern void func_0809CC3C(Object0809D86C *object, Owner0809D86C *owner,
                          s8 direction);
extern BufferInitializer0809D86C const g_callbacks_0836D4B8[];

/* Complete [0x0809D86C, 0x0809D8B4): 72 bytes, 31 instructions. */
Object0809D86C *func_0809D86C(Owner0809D86C *owner, u8 direction, u16 value)
{
    Object0809D86C *object = func_08022840(sizeof(*object));

    g_callbacks_0836D4B8[0](object, sizeof(*object));
    object->value = value;
    func_0809CC3C(object, owner, (s8)direction);
    return object;
}
