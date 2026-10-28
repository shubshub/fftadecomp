#include "ffta.h"

/* Target: complete [0x081342CC, 0x081343C8), 252 bytes. */
typedef struct {
    u8 unknown_00[0xe8];
    u8 known[8];
} AbilityObject;

typedef struct {
    const void *source;
    const AbilityObject *object;
    u8 unknown_08[8];
    u8 bits[8];
    u16 value_18;
    u8 unknown_1A[12];
    u16 flags;
} AbilityContext;

typedef struct {
    u8 unknown_00[0x70];
    u32 bits[2];
    u16 value_78;
} AbilityState;

extern AbilityContext data_0200F3F0;
extern AbilityState g_state_0200F390;
extern void func_0812F2A4(u16, u16, u8);
extern void func_0812F328(u8);
extern u8 func_08130FBC(void);
extern void func_0812F34C(const AbilityObject *);
extern void func_0812F39C(s32);
extern s32 func_08131B20(void);
extern u8 func_0812F358(void);
extern void func_0813388C(void);

static inline u32 test_bit(const u8 *bits, s32 bit)
{
    s32 byte = bit >> 3;
    s32 shift = bit & 7;

    return (bits[byte] >> shift) & 1;
}

static inline void clear_value(AbilityContext *context)
{
    context->value_18 = 0;
}

u8 func_081342CC(const void *source, const AbilityObject *object,
                 u16 ability, u16 parameter, s32 bit, u8 require_known)
{
    s32 index;

    if (ability == 0)
        return 1;
    if (require_known && !test_bit(object->known, bit))
        return 0;

    func_0812F2A4(ability, parameter, 0);
    data_0200F3F0.flags |= 0x10;
    data_0200F3F0.source = source;
    data_0200F3F0.object = object;

    for (index = 0; index < 3; index++) {
        func_0812F328(index);
        if (func_08130FBC()) {
            func_0812F34C(object);
            func_0812F39C(index);
            if (!func_08131B20() && !func_0812F358()) {
                g_state_0200F390.bits[0] = 0;
                g_state_0200F390.bits[1] = 0;
                if (!require_known) {
                    clear_value((AbilityContext *)((u8 *)&g_state_0200F390 + 0x60));
                    func_0813388C();
                    if (test_bit(data_0200F3F0.bits, bit))
                        return 1;
                } else {
                    g_state_0200F390.bits[0] = *(const u32 *)object->known;
                    g_state_0200F390.bits[1] = *(const u32 *)(object->known + 4);
                    clear_value((AbilityContext *)((u8 *)&g_state_0200F390 + 0x60));
                    func_0813388C();
                    if (!test_bit(data_0200F3F0.bits, bit))
                        return 1;
                }
            }
        }
    }
    return 0;
}
