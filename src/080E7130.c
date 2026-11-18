#include "ffta.h"
#include "effect_task.h"

/* Complete target [0x080E7130, 0x080E72B4): 388 bytes, 170 instructions.
 * f0b54f464646c0b483b081468846171c09888020400081421cd0814202dc0029
 * 0cd0a7e00448814200d187e00130814200d190e09ee000000101000041464868
 * b860898a3970b91c3a1dbb1df6f7e4faf8608fe01b4e02203a5e04217b5e0621
 * 785e0090184d019507240294301c0421eef76efe386102203a5e04217b5e0621
 * 785e009001950294301c0521eef760fe786138690121494229f746ff78690121
 * 29f742ff0024b8680021f6f753fa000600280bd0f86814214a46f8f78ffbb861
 * 01240ae030614f084d030000b868f6f769f90004002800dd022439780125281c
 * 08400223002800d00423b868a10009198900104a891800934a4601921e220292
 * 0c220023f5f7d6fef8613978281c08400822002800d01022074804210a434946
 * 009101210023f8f799fd38624246108801301ee090773908dc773908381c1030
 * 0221eef757fe0006002813d041460888013008800ee0b869f4f7e8fbb8610028
 * 08d1f869f4f7e2fbf861002802d1022042461080002003b018bc9846a146f0bc
 * 02bc0847
 */

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    s16 index;
} EffectDescriptor;

typedef struct {
    u8 index;
    u8 unknown_01;
    s16 x;
    s16 y;
    s16 z;
    void *wrapper;
    void *underlying;
    void *resources[2];
    void *auxiliary;
    void *effect;
    void *record;
} EffectState;

extern const u8 data_084F6130[];
extern const u8 data_08397790[];
extern const u8 data_083977DC[];

extern void *func_080DD748(void *wrapper, s16 *x, s16 *y, s16 *z);
extern void *func_080D5E80(const void *data, u16 index, s16 x, s16 y, s16 z,
                           s16 value, u8 option);
extern void func_08011058(void *object, s16 value);
extern u8 func_080DD684(const void *wrapper, u8 kind);
extern s16 func_080DD4D4(const void *wrapper);
extern void *func_080DF90C(void *target, u32 value, void *context);

extern void *func_080DFD8C(const void *events, u8 count, u16 flags,
                           u16 delay, void *parent);
extern u8 func_080D5F24(void **objects, u16 count);
extern void *func_080DBA5C(void *attachment);

u32 func_080E7130(void *task, EffectDescriptor *effect, EffectState *state)
{
    u32 selector;
    u32 priority;
    u32 flags;

    switch (effect->state) {
    case 0:
        state->wrapper = effect->object;
        state->index = effect->index;
        state->underlying = func_080DD748(state->wrapper, &state->x, &state->y,
                                          &state->z);
        break;
    case 0x100:
        state->resources[0] = func_080D5E80(data_084F6130, 4, state->x, state->y,
                                            state->z, 0x34D, 7);
        state->resources[1] = func_080D5E80(data_084F6130, 5, state->x, state->y,
                                            state->z, 0x34D, 7);
        func_08011058(state->resources[0], -1);
        func_08011058(state->resources[1], 1);
        selector = 0;
        if (func_080DD684(state->wrapper, 0)) {
            state->auxiliary = func_080DF90C(state->underlying, 20, task);
            selector = 1;
        } else if (func_080DD4D4(state->wrapper) > 0) {
            selector = 2;
        }
        priority = (state->index & 1) ? 4 : 2;
        state->effect = func_080DCFE4(state->wrapper, data_08397790 + selector * 20,
                                      12, 0, priority, task, 30);
        flags = (state->index & 1) ? 0x10 : 8;
        state->record = func_080DFD8C(data_083977DC, 1, flags | 4, 0, task);
        effect->state++;
        break;
    case 0x101:
        if (func_080D5F24(state->resources, 2))
            effect->state++;
        break;
    case 0x102:
        state->auxiliary = func_080DBA5C(state->auxiliary);
        if (state->auxiliary)
            break;
        state->effect = func_080DBA5C(state->effect);
        if (state->effect)
            break;
        effect->state = 2;
        break;
    }
    return 0;
}
