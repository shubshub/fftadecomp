#include "control_flags.h"

struct RestoreState {
    u8 unknown_000[0x290];
    void *resource;
    u8 unknown_294[0x3c];
    void *context;
    u16 bg2hofs;
    u16 bg2vofs;
    u8 blend_control_low;
    u8 blend_control_high;
    u8 blend_alpha_low;
    u8 blend_alpha_high;
};

extern void func_08022854(void *);
extern void func_080920D0(void *);

/* Target bytes: 10b5041ca421890060180068002801d092f7fcffb4229200a018006802f034fc1a4bb6218900601800781a1c4a3211781070174aa01800781a1c4b3211781070144960180178181c4c3002780170124aa01800781a1c4d3211781070b521890060180088598a58820c4aa0180088998a988219888022d200101c08431880201c92f7c4ff10bc01bc0047000040090003d9020000da020000db020000d6020000 */
void func_0808F848(struct RestoreState *state)
{
    if (state->resource)
        func_08022854(state->resource);
    func_080920D0(state->context);
    g_control_flags_03000940.bldcnt_lo = state->blend_control_low;
    g_control_flags_03000940.bldcnt_hi = state->blend_control_high;
    g_control_flags_03000940.bldalpha_lo = state->blend_alpha_low;
    g_control_flags_03000940.bldalpha_hi = state->blend_alpha_high;
    g_control_flags_03000940.bg2hofs = state->bg2hofs;
    g_control_flags_03000940.bg2vofs = state->bg2vofs;
    g_control_flags_03000940.display |= 0x400;
    func_08022854(state);
}
