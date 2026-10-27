#include "ffta.h"

struct BlendState080D3F84 {
    u8 unknown_00[5];
    u8 effect;
    u8 first_targets;
    u8 second_targets;
};

struct DisplayControl080D3F84 {
    u8 unknown_00[0x4A];
    u8 blend_first : 8;
    u8 blend_second : 8;
};

extern struct DisplayControl080D3F84 g_control_flags_03000940;
extern struct BlendState080D3F84 *func_08005BFC(void *task);

/* Complete [0x080D3F84, 0x080D3FC8): 68 bytes, 31 instructions. */
void func_080D3F84(void *task, u8 first_targets, u8 second_targets)
{
    struct BlendState080D3F84 *blend = func_08005BFC(task);

    if (first_targets != 0xFF)
        blend->first_targets = first_targets;
    if (second_targets != 0xFF)
        blend->second_targets = second_targets;
    g_control_flags_03000940.blend_first =
        (blend->effect << 6) | blend->first_targets;
    g_control_flags_03000940.blend_second = blend->second_targets;
}
