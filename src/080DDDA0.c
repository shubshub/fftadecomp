#include "ffta.h"

typedef struct {
    void *object;
} Struct080DDDA0;

extern u8 func_080DD684(Struct080DDDA0 *state, u8 kind);
extern void *func_080DD34C(void *object);
extern void *func_080DD350(void *object);
extern u32 func_080DD71C(const void *object);
extern void func_0809A2D8(void *object, u16 action, s8 value);
extern void func_080DE33C(void *object, s8 value, u8 option);

static inline void dispatch_object_action(void *object, u16 action, s8 value)
{
    func_0809A2D8(func_080DD350(object), action, value);
}

/* 0x080DDDA0 - 124 bytes.
 * Target: 70b5041c09060e0e00250121fff76afc0006002813d1201c0221fff763fc00060028
 *         01d0242514e02068fff7bffafff7a5fc0004010c08200840002801d00c2507e0
 *         802000010840002800d02425002d0bd02068fff7aafa34062416fff7a8fa291c
 *         221cbcf768fa05e0206831060916002200f093fa70bc01bc0047
 */
void func_080DDDA0(Struct080DDDA0 *state, s8 value)
{
    u16 action = 0;

    if (func_080DD684(state, 1)) {
        action = 12;
    } else if (func_080DD684(state, 2)) {
        action = 36;
    } else {
        u16 flags = func_080DD71C(func_080DD34C(state->object));

        if (flags & 0x08)
            action = 12;
        else if (flags & 0x800)
            action = 36;
    }
    if (action)
        dispatch_object_action(func_080DD34C(state->object), action, value);
    else
        func_080DE33C(state->object, value, 0);
}
