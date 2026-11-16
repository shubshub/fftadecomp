#include "ffta.h"

/* Complete [0x080CEC78, 0x080CECF2): 122 bytes, 53 instructions, including
 * the two-word literal pool at 0x080CECCC.
 * 70b50004000c09060c0e1206160e3621fff728fc051c002d01d100202ae0600000194201
 * 0b49521880000b494018417801200840002811d00220084000280dd09019413000786843
 * 642173f0f5fe281a10e0000084895208b42c0002101c4030017801300078000208436843
 * 642173f0e3fe281870bc02bc0847
 */

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[10];
} FlagRecord080CEC78;

/* 96-byte rows, packed: every multi-byte member is read a byte at a time -
 * percent here (0x080CECD4-0x080CECE0), mask in src/080CC958.c (packed,
 * 0x080CC974-0x080CC986) and the 1-based entries in src/080CC9A0.c and
 * src/080CC9F0.c (0x080CC9CC-0x080CC9D2, 0x080CCA12-0x080CCA18). */
typedef struct {
    u32 mask;
    u16 entries[30];
    u16 percent;
    u8 entry_percents[0x1E];
} __attribute__((packed)) Row080CEC78;

extern const Row080CEC78 g_table_08528984[];
extern FlagRecord080CEC78 g_state_02002CB4[];

extern u32 func_080CE4DC(u16 index, u8 selector);
extern u32 func_08142AB0(u32 value, u32 divisor);

u32 func_080CEC78(u16 index, u8 slot, u8 entry)
{
    u32 value = func_080CE4DC(index, 0x36);
    const Row080CEC78 *row;
    FlagRecord080CEC78 *state;

    if (value == 0)
        return 0;
    row = &g_table_08528984[slot];
    state = &g_state_02002CB4[slot];
    if ((state->flags & 1) && (state->flags & 2))
        return value - func_08142AB0(row->entry_percents[entry - 1] * value, 100);
    return value + func_08142AB0(row->percent * value, 100);
}
