#include "ffta.h"

typedef struct State0801B7F8 State0801B7F8;

extern void func_0801AF08(State0801B7F8 *state, void *first, void *second,
                          void *buffer, void *secondary_buffer, u8 enabled);

/* 0x0801B7F8 - 28 bytes.
 * Target: 30b582b0059d069c2406240e00950194fff77efb02b030bc01bc0047
 */
void func_0801B7F8(State0801B7F8 *state, void *first, void *second,
                   void *buffer, void *secondary_buffer, u8 enabled)
{
    func_0801AF08(state, first, second, buffer, secondary_buffer, enabled);
}
