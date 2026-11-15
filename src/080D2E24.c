#include "ffta.h"

/* Complete [0x080D2E24, 0x080D2E60): 60 bytes, 23 instructions, two-word pool.
 * 30b50c4d0c4c8021c9002a68201c6ff00bfa8021c9006018c02189002a686ff003fa
 * e020c00024180020206030bc01bc00470000b8d43608c8210002
 */

typedef struct {
    u8 unknown_0000[0x21C8];
    u8 unknown_21C8[0x400];
    u8 unknown_25C8[0x300];
    void *head;
} State080D2E24;

extern State080D2E24 g_state_02000000;
extern void (*g_callbacks_0836D4B8[])(void *, u32);

void func_080D2E24(void)
{
    g_callbacks_0836D4B8[0](g_state_02000000.unknown_21C8,
                            sizeof(g_state_02000000.unknown_21C8));
    g_callbacks_0836D4B8[0](g_state_02000000.unknown_25C8,
                            sizeof(g_state_02000000.unknown_25C8));
    g_state_02000000.head = 0;
}
