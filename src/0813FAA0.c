#include "control_flags.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tile_map;
} Display0813FAA0;

extern Display0813FAA0 data_030008B0;
extern u8 data_06004C20[];
extern void func_0813FB68(u16);
extern void func_0813FB7C(void *, u16);
extern void func_0813FBB0(void *, u16, u16);
extern void func_0813FBD4(u16 *, u8, u8, u8, u8);

/* Complete target [0x0813FAA0, 0x0813FB0C): 108 bytes.
 * 30b581b0fe2000f05ff814480e2100f065f8134c608a00206082608aa18aa082104d686910490f2200f072f868690b210091082105220e2300f07cf821888022d200101c0843208042342178042022780843207001b030bc01bc0047204c000640090003b008000361020000
 */
void func_0813FAA0(void)
{
    func_0813FB68(254);
    func_0813FB7C(data_06004C20, 14);
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs;
    func_0813FBB0(data_030008B0.tile_map, 609, 15);
    func_0813FBD4(data_030008B0.tile_map, 8, 5, 14, 11);
    g_control_flags_03000940.display |= 0x400;
    g_control_flags_03000940.winin_lo |= 4;
}
