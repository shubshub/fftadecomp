/* Target 0x080E7130 .. 0x080E72B4, 388 bytes:
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
#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 flags;
} EffectDescriptor;

typedef struct {
    u8 flags;
    u8 unknown_01;
    s16 coordinate_x;
    s16 coordinate_y;
    s16 coordinate_z;
    void *wrapper;
    void *underlying;
    void *resources[2];
    void *auxiliary_child;
    void *effect_child;
    void *record_child;
} EffectState;

extern void *func_080DD748(void *wrapper, s16 *coordinate_x,
                         s16 *coordinate_y, s16 *coordinate_z);
extern void *func_080D5E80(const void *record, u16 kind, s16 coordinate_x,
                         s16 coordinate_y, s16 coordinate_z, s16 value, u8 option);
extern void func_08011058(void *resource, s16 value);
extern u8 func_080DD684(void *wrapper, u8 selector);
extern s16 func_080DD4D4(const void *wrapper);
extern void *func_080DF90C(void *underlying, u16 value, void *parent);
extern void *func_080DCFE4(void *wrapper, const void *record, u8 kind,
                         u16 delay, u16 flags, void *parent, s16 duration);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                         u16 delay, void *parent);
extern u32 func_080D5F24(void **resources, u16 count);
extern void *func_080DBA5C(void *task);

u32 func_080E7130(void *task, void *descriptor, void *payload)
{
    EffectDescriptor *effect = descriptor;
    EffectState *state = payload;
    u32 selector;

    switch (effect->phase) {
    case 0:
        state->wrapper = effect->object;
        state->flags = effect->flags;
        state->underlying = func_080DD748(state->wrapper, &state->coordinate_x,
                                         &state->coordinate_y, &state->coordinate_z);
        break;
    case 0x100:
        state->resources[0] = func_080D5E80((const void *)0x084F6130, 4,
                                          state->coordinate_x, state->coordinate_y,
                                          state->coordinate_z,
                                          0x34D, 7);
        state->resources[1] = func_080D5E80((const void *)0x084F6130, 5,
                                          state->coordinate_x, state->coordinate_y,
                                          state->coordinate_z,
                                          0x34D, 7);
        func_08011058(state->resources[0], -1);
        func_08011058(state->resources[1], 1);
        selector = 0;
        if (func_080DD684(state->wrapper, 0)) {
            state->auxiliary_child = func_080DF90C(state->underlying, 20, task);
            selector = 1;
        } else if (func_080DD4D4(state->wrapper) > 0) {
            selector = 2;
        }
        state->effect_child = func_080DCFE4(state->wrapper,
                                          (const u8 *)0x08397790 + 20 * selector,
                                          12, 0, (state->flags & 1) ? 4 : 2,
                                          task, 30);
        state->record_child = func_080DFD8C((const void *)0x083977DC, 1,
                                          ((state->flags & 1) ? 0x10 : 8) | 4,
                                          0, task);
        effect->phase++;
        break;
    case 0x101:
        if ((u8)func_080D5F24(state->resources, 2))
            effect->phase++;
        break;
    case 0x102:
        state->auxiliary_child = func_080DBA5C(state->auxiliary_child);
        if (state->auxiliary_child)
            break;
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child)
            break;
        effect->phase = 2;
        break;
    }
    return 0;
}
