#include "ffta.h"

typedef struct {
    void *object;
    void *first;
    void *second;
    u8 unknown_0C[0x20];
} EffectEntry080A80C8;

typedef struct {
    u8 unknown_00[0x20];
    EffectEntry080A80C8 entries[14];
    void *tasks[14];
    u8 count;
} EffectSequence080A80C8;

typedef struct {
    EffectSequence080A80C8 sequences[14];
    u8 unknown_26B8[5];
    u8 count;
} EffectState080A80C8;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_0809D8C4(void *object);
extern void func_080A8990(void *object);
extern void func_080A53E4(EffectSequence080A80C8 *sequence);
extern void func_08022854(void *object);
extern void func_0802D714(void);

static inline void end_sequences(EffectState080A80C8 *state)
{
    s32 j;

    for (j = 0; j < state->count; j++)
        func_080A53E4(&state->sequences[j]);
}

/* Complete [0x080A80C8, 0x080A8194): 204 bytes.
 * f0b557464e464546e0b4051c00222c496818007882422edab1239b009a460026514651436818b0239b00c018013291460278964219da8846071c2c2070434346c418281c243000190068002801d0f5f7d5fb281c283000190068002801d000f033fc013638788642e7db4a461449681800788242d3db0026114aa818071c3b789e420ada2c1c201cfdf748f9b12080002418013639788e42f5db0a480a490268281c9af06ff8281c7af770fb85f7cefa38bc9846a146aa46f0bc01bc00470000bd260000b8d4360898340000
 */
void func_080A80C8(EffectState080A80C8 *state)
{
    s32 i;
    s32 j;

    for (i = 0; i < state->count; i++) {
        for (j = 0; j < state->sequences[i].count; j++) {
            if (state->sequences[i].entries[j].first)
                func_0809D8C4(state->sequences[i].entries[j].first);
            if (state->sequences[i].entries[j].second)
                func_080A8990(state->sequences[i].entries[j].second);
        }
    }
    end_sequences(state);
    g_callbacks_0836D4B8[0](state, 0x3498);
    func_08022854(state);
    func_0802D714();
}
