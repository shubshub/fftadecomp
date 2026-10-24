/* Target 0x081451C0, 44 bytes:
 * 00b50004074a0849400b401883885900c918890089180a680168101c00f066fb01bc004724bb140848bb1408
 */

#include "ffta.h"

typedef struct State081458AC State081458AC;
typedef struct Data081458AC Data081458AC;

typedef struct {
    State081458AC *state;
    u32 unknown_04;
    u32 unknown_08;
} StateEntry081451C0;

typedef struct {
    const Data081458AC *data;
    u16 state_index;
    u16 unknown_06;
} DataEntry081451C0;

void func_081458AC(State081458AC *state, const Data081458AC *data);

void func_081451C0(u16 index)
{
    const StateEntry081451C0 *states = (const StateEntry081451C0 *)0x0814BB24;
    const DataEntry081451C0 *entry = (const DataEntry081451C0 *)0x0814BB48 + index;

    func_081458AC(states[entry->state_index].state, entry->data);
}
