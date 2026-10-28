#include "ffta.h"

typedef struct __attribute__((packed)) SelectedResource08019268 {
    u32 id : 10;
    u32 value : 8;
} SelectedResource08019268;

typedef struct ResourceSelection08019268 {
    const SelectedResource08019268 *current;
} ResourceSelection08019268;

extern ResourceSelection08019268 g_state_020020D0;
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x08019268, 0x0801928C): 36 bytes, 14 instructions. */
u32 func_08019268(u8 *destination)
{
    func_08018ABC(destination, g_state_020020D0.current->value);
    return 0;
}
