#include "ffta.h"

/* Complete [0x0804AD44, 0x0804ADC8): 132 bytes, 57 instructions. */
typedef struct {
    u8 unknown_000[0xEDC];
    u8 field_edc;
    u8 field_edd;
    u8 unknown_EDE[2];
    u8 field_ee0;
    u8 field_ee1;
    u8 unknown_EE2[0x3A];
    u8 count;
    u8 state;
    u8 unknown_F1E;
    u8 selection;
    u8 previous_selection;
    u8 field_f21;
} State0804AD44;

extern State0804AD44 *g_state_03002810;

void func_0804AD44(u8 first, u8 second, u8 third, u8 fourth,
                   u8 selection, u8 last)
{
    g_state_03002810->field_edc = first;
    g_state_03002810->field_edd = second;
    g_state_03002810->field_ee0 = third;
    g_state_03002810->field_ee1 = fourth;
    g_state_03002810->count = 2;
    g_state_03002810->state = 0;
    g_state_03002810->selection = selection;
    g_state_03002810->previous_selection = 0xFF;
    g_state_03002810->field_f21 = last;
}
