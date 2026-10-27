#include "ffta.h"

typedef struct ChildState0805FD04 {
    u8 unknown_00[6];
    u8 index;
    u8 unknown_07[0x8D];
    void *child;
} ChildState0805FD04;

typedef struct ChildContext0805FD04 {
    u8 unknown_00[8];
    void *children[2];
    u8 ready[2];
} ChildContext0805FD04;

extern ChildContext0805FD04 *data_0200F44C;
extern void func_08005B40(void *object);

/* Complete [0x0805FD04, 0x0805FD38): 52 bytes, 22 instructions. */
void func_0805FD04(ChildState0805FD04 *state)
{
    ChildContext0805FD04 *context;

    func_08005B40(state->child);
    context = data_0200F44C;
    context->children[state->index] = 0;
    context->ready[state->index] = 1;
}
