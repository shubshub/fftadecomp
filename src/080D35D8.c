#include "control_flags.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[0xADA];
    u16 bg2cnt;
    u16 bg3cnt;
    u8 unknown_AE2[8];
    u16 bg2hofs;
    u16 bg2vofs;
    u16 bg3hofs;
    u16 bg3vofs;
} DisplayState080D35D8;
extern void *data_020159C0;
extern u8 data_06005800[], data_06005000[];
extern void *func_08005BFC(void *task);
extern void func_08003620(u8 value);
extern u16 func_080035A8(u8 index);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, int, void *, unsigned);

/* Complete target bytes: 30b52b48006832f70dfb041c002030f71bf802202ff7dcff264d29888143298003202ff7d5ff2988814323480140234801402980224960180088e988e880214960180088698a68821f4960180088a98aa882ae21090160180088298928811b4960180088e98ae882af21090160180088298b2883618810200840002804d1281c4a3001780021017000f04afa104a8024e4000021231c2df757fa00f041fa0d4a0021231c2df750fa30bc01bc00470000c059010240090003ff9f0000ff7f0000de0a0000ea0a0000ec0a0000ee0a00000058000600500006 */
void func_080D35D8(void)
{
    DisplayState080D35D8 *state = func_08005BFC(data_020159C0);
    func_08003620(0);
    g_control_flags_03000940.display &= ~func_080035A8(2);
    g_control_flags_03000940.display &= ~func_080035A8(3);
    g_control_flags_03000940.display &= 0x9FFF;
    g_control_flags_03000940.display &= 0x7FFF;
    g_control_flags_03000940.bg2cnt = state->bg2cnt;
    g_control_flags_03000940.bg2hofs = state->bg2hofs;
    g_control_flags_03000940.bg2vofs = state->bg2vofs;
    g_control_flags_03000940.bg3cnt = state->bg3cnt;
    g_control_flags_03000940.bg3hofs = state->bg3hofs;
    g_control_flags_03000940.bg3vofs = state->bg3vofs;
    if ((state->flags & 16) == 0)
        g_control_flags_03000940.bldcnt_lo = 0;
    func_08000B20(func_080D3AF8(), 0, data_06005800, 0x400);
    func_08000B20(func_080D3AF8(), 0, data_06005000, 0x400);
}
