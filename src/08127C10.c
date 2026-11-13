#include "ffta.h"

// Target: complete [0x08127C10, 0x08127C54), 68 bytes including literal.
typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Output08127C10;

typedef struct {
    u8 selector;
    u8 flags;
    s16 x;
    s16 y;
    u16 value;
} Placement08127C10;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    Output08127C10 *output;
    s32 x;
    s32 y;
    u32 unknown_10;
    u16 selector;
    u16 flags;
    u16 value;
} Descriptor08127C10;

typedef u32 (*TaskCallback08127C10)(void *task, void *descriptor, void *payload);

extern u32 func_08127990(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback08127C10 callback, u16 payload_size,
                           void *descriptor, void *parent);

void func_08127C10(Output08127C10 *output, Placement08127C10 placement)
{
    Descriptor08127C10 descriptor;

    output->complete = 0;
    descriptor.output = output;
    descriptor.x = placement.x;
    descriptor.y = placement.y;
    descriptor.selector = placement.selector;
    descriptor.flags = placement.flags;
    descriptor.value = placement.value;
    func_08121B8C(func_08127990, 0x140, &descriptor, output->parent);
}
