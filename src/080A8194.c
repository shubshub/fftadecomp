#include "ffta.h"

/* Complete [0x080A8194, 0x080A8264): 208 bytes, 90 instructions, including
 * the four-word literal pool at 0x080A8254.
 * f0b557464e464546e0b488b004901098129c0904090c05911204120c06921b061b0e9946
 * 0006000e82462406240e0794234c201c7af73afb061c22480268301c211c9af039f8b120
 * 80008046351c1c35341c1d4977181b480268201c41469af02bf8ff202870b12080002d18
 * 2418bc42f1dd49460a061216504603061b16059900910698019011980006000e02900799
 * 0391301c0499fcf787f80c4970180078002803d1301c7af70bfb0026301c08b038bc9846
 * a146aa46f0bc02bc0847000098340000b8d43608f4230000bd260000
 *
 * Allocates and clears the 0x3498-byte effect state, resets each of its 14
 * sequences, then lets func_080A433C fill it; an empty result (count 0) is
 * freed and 0 returned.
 */

typedef struct {
    void *object;
    void *first;
    void *second;
    u8 unknown_0C[0x20];
} EffectEntry080A8194;

typedef struct {
    u8 unknown_00[0x1C];
    u8 unknown_1C;
    u8 unknown_1D[3];
    EffectEntry080A8194 entries[14];
    void *tasks[14];
    u8 count;
} EffectSequence080A8194;

typedef struct {
    EffectSequence080A8194 sequences[14];
    u8 unknown_26B8[5];
    u8 count;
} EffectState080A8194;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern void func_080A433C(EffectState080A8194 *state, void *context, s8 first,
                          s8 second, u16 value_a, u16 value_b, u8 flag,
                          u8 variant);

/* Resets one sequence record: clears its 0x2C4 bytes and sets byte 0x1C to
 * 0xFF (the loop body at 0x080A81EA..0x080A81F8).  The ROM has no
 * out-of-line copy and no second expansion of it; the module's other
 * per-sequence routines are func_080A87B4 (allocate and clear) and
 * func_080A87DC (clear and free). */
static inline void reset_sequence(EffectSequence080A8194 *sequence)
{
    g_callbacks_0836D4B8[0](sequence, sizeof(EffectSequence080A8194));
    sequence->unknown_1C = 0xFF;
}

EffectState080A8194 *func_080A8194(void *context, u16 value_a, u16 value_b,
                                   u8 first, u8 second, s32 flag, u8 variant)
{
    EffectState080A8194 *state;
    s32 i;

    state = func_08022840(0x3498);
    g_callbacks_0836D4B8[0](state, 0x3498);
    for (i = 0; i < 14; i++)
        reset_sequence(&state->sequences[i]);
    func_080A433C(state, context, first, second, value_a, value_b, flag,
                  variant);
    if (state->count == 0) {
        func_08022854(state);
        state = 0;
    }
    return state;
}
