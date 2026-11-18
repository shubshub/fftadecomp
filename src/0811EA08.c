#include "effect_registry.h"

/* Target: complete [0x0811EA08, 0x0811EA66), 94 bytes, 44 instructions.
 * These are offset views; complete object extents remain unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *context;
    u8 unknown_08[12];
    s16 selector;
} Descriptor0811EA08;

typedef struct {
    void *child;
} Payload0811EA08;


extern void func_080D35D8(void);
extern void *func_080D3888(void *task);

u32 func_0811EA08(void *task, Descriptor0811EA08 *descriptor,
                  Payload0811EA08 *payload)
{
    switch (descriptor->phase) {
    case 0:
        if (descriptor->selector == 0x19a)
            payload->child = func_080D3508(0x165, 0, (u32)descriptor->context);
        else
            payload->child = func_080D3508(0x164, 0, (u32)descriptor->context);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->child = func_080D3888(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
