/* Target bytes (60):
 * 00 b5 00 06 01 0e 0b 48 0b 4a 83 18 1a 78 90 07
 * 80 0f 81 42 0c d0 03 20 01 40 04 20 40 42 10 40
 * 08 43 18 70 00 f0 0a f8 12 f0 0c fc 00 f0 0a f9
 * 01 bc 00 47 00 00 00 02 c2 2f 00 00
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FC2];
    unsigned mode : 2;
} State08135CFC;

extern State08135CFC g_state_02000000;
extern void func_08135D38(void);
extern void func_08148540(void);
extern void func_08135F40(void);

void func_08135CFC(u8 mode)
{
    if (mode != g_state_02000000.mode) {
        g_state_02000000.mode = mode;
        func_08135D38();
        func_08148540();
        func_08135F40();
    }
}
