#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F69];
    u8 selector;
    u8 unknown_1F6A[0x2E54 - 0x1F6A];
    u8 selection : 5;
    u8 unknown_05 : 3;
} SelectionState08043F64;

extern SelectionState08043F64 g_state_02000000;

/* 08043F64..08043F90: 44 bytes, including literal pool.
 * 074a084813181978202040420840122108431870c006c00e0349521810707047
 * 00000002542e0000691f0000
 */
void func_08043F64(void)
{
    g_state_02000000.selection = 18;
    g_state_02000000.selector = g_state_02000000.selection;
}
