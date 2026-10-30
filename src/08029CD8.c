#include "ffta.h"

typedef struct {
    u8 unknown_00[0x7C];
    void *item;
    void *context;
    u8 unknown_84[0x1001];
    u8 field_1085;
    u8 field_1086;
    u8 unknown_1087;
    u8 field_1088;
} State08029CD8;

extern void *func_08021618(void *context, void *item, u32 zero, u32 mode,
                           u32 first, u32 second, u32 last);

/* Complete target [0x08029CD8, 0x08029D20), 72 bytes.
 * 70b583b0041c0d482318002519700c4960180270201c80300068e16f094ea219
 * 127800921a780192029500221423f7f787fce06703b070bc01bc004786100000
 * 8810000085100000
 */
void func_08029CD8(State08029CD8 *state, u8 first, u8 second)
{
    state->field_1086 = first;
    state->field_1088 = second;
    state->item = func_08021618(state->context, state->item, 0, 20,
                               state->field_1085, state->field_1086, 0);
}
