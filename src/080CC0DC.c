#include "ffta.h"

extern u8 g_state_02000000[];
extern u32 func_08002804(void);

/* Complete target: [0x080CC0DC, 0x080CC198), 188 bytes. */
void func_080CC0DC(void)
{
    do {
        g_state_02000000[0x2E5E] = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000[0x2E5E] == 3 || g_state_02000000[0x2E5E] == 5);

    do {
        g_state_02000000[0x2E5F] = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000[0x2E5F] == g_state_02000000[0x2E5E] ||
             g_state_02000000[0x2E61] == 3 || g_state_02000000[0x2E61] == 5);

    do {
        g_state_02000000[0x2E60] = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000[0x2E60] == 3 || g_state_02000000[0x2E60] == 5);

    do {
        g_state_02000000[0x2E61] = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000[0x2E61] == g_state_02000000[0x2E60] ||
             g_state_02000000[0x2E61] == 3 || g_state_02000000[0x2E61] == 5);
}
