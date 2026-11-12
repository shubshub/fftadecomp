#include "control_flags.h"

typedef struct {
    u8 unknown_000[0x47C];
    u16 display;
    u8 blend_control_low;
    u8 blend_control_high;
    u8 first_weight;
    u8 second_weight;
} DisplayObject080917F8;

extern void func_08022854(u8 *object);

/* Complete [0x080917F8, 0x0809185C): 100 bytes, including five literal words. */
void func_080917F8(DisplayObject080917F8 *object)
{
    g_control_flags_03000940.display = object->display;
    g_control_flags_03000940.bldcnt_lo = object->blend_control_low;
    g_control_flags_03000940.bldcnt_hi = object->blend_control_high;
    object->first_weight = g_control_flags_03000940.bldalpha_lo;
    object->second_weight = g_control_flags_03000940.bldalpha_hi;
    func_08022854((u8 *)object);
}
