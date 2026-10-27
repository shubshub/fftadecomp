#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} Resource080194A8;

typedef struct {
    const Resource080194A8 *current;
    u8 unknown_04[8];
    u16 id;
} Selection080194A8;

extern Selection080194A8 g_state_020020D0;
extern u32 func_080CE4DC(u16 id, u32 field);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x080194A8, 0x080194E2): 58 bytes, 24 instructions. */
u32 func_080194A8(u8 *destination)
{
    u16 id = g_state_020020D0.current
        ? g_state_020020D0.current->id : g_state_020020D0.id;

    func_08018ABC(destination, func_080CE4DC(id, 0x1E));
    return 0;
}
