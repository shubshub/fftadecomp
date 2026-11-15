#include "ffta.h"

/* Target: complete [0x081342CC, 0x081343C8), 252 bytes, 112 instructions,
 * including the data_0200F3F0 and g_state_0200F390 literals.
 * The two eight-byte bit sets are copied and cleared as two words and tested
 * a byte at a time. */
typedef union {
    u8 bytes[8];
    u32 words[2];
} BitSet;

typedef struct {
    u8 unknown_00[0xE8];
    BitSet bits;
} Unit;

typedef struct {
    const void *source;
    const Unit *target;
    u8 unknown_08[8];
    BitSet bits;
    u16 value_18;
    u8 unknown_1A[12];
    u16 flags;
} ActionState;

typedef struct {
    u8 unknown_00[0x60];
    ActionState action;
} State;

extern ActionState data_0200F3F0;
extern State g_state_0200F390;
extern void func_0812F2A4(u16 action, u16 equipment, u8 kind);
extern void func_0812F328(u8 index);
extern u8 func_08130FBC(void);
extern void func_0812F34C(const Unit *target);
extern void func_0812F39C(s32 index);
extern s32 func_08131B20(void);
extern u8 func_0812F358(void);
extern void func_0813388C(void);

static inline u8 test_bit(const u8 *bits, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;

    return (bits[byte_index] >> bit_index) & 1;
}

u8 func_081342CC(const void *source, const Unit *target, u16 action,
                 u16 equipment, s32 bit, u8 require_set)
{
    ActionState *state;
    s32 index;

    if (action == 0)
        return 1;
    if (require_set && !test_bit(target->bits.bytes, bit))
        return 0;

    func_0812F2A4(action, equipment, 0);
    data_0200F3F0.flags |= 0x10;
    data_0200F3F0.source = source;
    data_0200F3F0.target = target;

    for (index = 0; index < 3; index++) {
        func_0812F328(index);
        if (func_08130FBC()) {
            func_0812F34C(target);
            func_0812F39C(index);
            if (!func_08131B20() && !func_0812F358()) {
                g_state_0200F390.action.bits.words[0] = 0;
                g_state_0200F390.action.bits.words[1] = 0;
                if (!require_set) {
                    state = &g_state_0200F390.action;
                    state->value_18 = 0;
                    func_0813388C();
                    if (test_bit(data_0200F3F0.bits.bytes, bit))
                        return 1;
                } else {
                    g_state_0200F390.action.bits.words[0] = target->bits.words[0];
                    g_state_0200F390.action.bits.words[1] = target->bits.words[1];
                    state = &g_state_0200F390.action;
                    state->value_18 = 0;
                    func_0813388C();
                    if (!test_bit(data_0200F3F0.bits.bytes, bit))
                        return 1;
                }
            }
        }
    }
    return 0;
}
