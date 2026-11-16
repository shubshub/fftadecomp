#include "ffta.h"

// Complete [0x080A8194, 0x080A8264): 208 bytes, 90 instructions.
// Allocate and clear the 0x3498-byte effect state, reset each of its 14
// sequences, then let func_080A433C fill it; an empty result is freed.

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
