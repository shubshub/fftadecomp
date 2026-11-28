#include "ffta.h"

/* Complete [0x080C286C, 0x080C2940): 212 bytes, 92 instructions. */

struct State080C286C {
    u8 unknown0000[4];
    /* +4..+0x5B is the selection func_080C26EC reads (its owner, 40 actions,
     * then limit and count, which it reads as the action index). */
    void **source;
    u8 unknown0008[0x50];
    u16 limit;
    u16 count;
    u8 slot1[0x290C];
    u8 slot0[0x2908];
    /* slot0's entry count: func_080C4830 reads base + 0x5270 as the count of
     * the 0x328-byte entries at base + 0x2968.  Read signed here (ldrsh at
     * 0x080C28B6 and 0x080C28FC). */
    s16 slot0_count;
    u8 unknown5272[0xD];
    u8 result;
    u8 phase;
};

extern s32 func_0812F0D8(const void *object, u16 *entries);
/* argument4 is s16 here: the caller passes slot0_count from an ldrsh
 * (src/080C26EC.c declares it u16 and only passes it on). */
extern u8 func_080C26EC(void *group, void *selection, u16 default_parameter,
                        s16 filter, s16 argument4, u8 index);

u32 func_080C286C(struct State080C286C *state)
{
    u16 entries[2];

    func_0812F0D8(*state->source, entries);
    if (state->count >= state->limit)
        return 0;

    switch (state->phase) {
    case 0:
        state->result = func_080C26EC(state->slot0, &state->source, entries[0], 0,
                                      state->slot0_count, state->result);
        if (state->result == 0xFF) {
            state->result = 0;
            state->phase = 1;
        }
        break;
    case 1:
        state->result = func_080C26EC(state->slot1, &state->source, entries[0], 0,
                                      state->slot0_count, state->result);
        if (state->result == 0xFF) {
            /* The ROM keeps both phase stores (strb at 0x080C291E, then 0
             * at 0x080C2928): case 0's completion, then the reset. */
            state->result = 0;
            state->phase = 1;
            state->count++;
            state->phase = 0;
        }
        break;
    }
    return 1;
}
