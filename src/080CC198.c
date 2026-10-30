#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2E5E];
    u8 previous_first;
    u8 previous_second;
    u8 current_first;
    u8 current_second;
} State080CC198;

extern State080CC198 g_state_02000000;
extern u32 func_08002804(void);

/* Complete target: [0x080CC198, 0x080CC218), 128 bytes.
 * Target bytes: 30b51a491a480b181a781a4c08190270194a881800780134091908701c1c36f725fb00040014092176f0c6fb013020700006000e0328f2d00528f0d00f4c651c36f714fb00040014092176f0b5fb013028700006000e21788842f1d00328efd00528edd030bc01bc0047000000000002602e00005e2e0000612e0000602e0002
 */
void func_080CC198(void)
{
    g_state_02000000.previous_first = g_state_02000000.current_first;
    g_state_02000000.previous_second = g_state_02000000.current_second;

    do {
        g_state_02000000.current_first = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000.current_first == 3 ||
             g_state_02000000.current_first == 5);

    do {
        g_state_02000000.current_second = (s16)func_08002804() % 9 + 1;
    } while (g_state_02000000.current_second == g_state_02000000.current_first ||
             g_state_02000000.current_second == 3 ||
             g_state_02000000.current_second == 5);
}
