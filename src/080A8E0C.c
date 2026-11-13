#include "ffta.h"

// 0x080A8E0C .. 0x080A8F60: 340 bytes, including literal pool.
typedef struct {
    u32 first;
    u32 second;
} Pair;

typedef struct {
    const u8 *graphics;
    u8 unknown_04[4];
    s16 number;
    u8 digits[4];
    s16 index;
    s16 remaining;
    u16 unknown_12;
    const u8 *current;
    const u8 *script;
    u8 unknown_1c;
    u8 playing;
    u8 mode;
    u8 unknown_1f[7];
    s16 x;
    s16 y;
} AnimationState;

typedef struct {
    u16 value;
    u16 unknown_02;
} OwnerEntry;

typedef struct {
    u8 unknown_00[0x4a];
    u16 base;
    u8 unknown_4c[0x588];
    OwnerEntry entries[1];
} Owner;

extern u16 data_0200F9D0[];
extern void (*data_08394044)(const void *, s32, s32, u8, u8, u8, u8, u8,
                             const u16 *, u8, u32, s32);

extern void func_080C7B78(const Pair *source, AnimationState **second,
                          u32 *first);
extern void func_080A8DB8(AnimationState *state);
extern void func_0801C960(s16 x, s16 y, s16 *first, s16 *second);
extern void func_08001F34(const void *, s32, s32, u8, u8, u8, u8, u8,
                          u32, u8, u32);

u32 func_080A8E0C(const Pair *source, Owner *owner)
{
    AnimationState *state;
    u32 first;
    s16 x, y;
    s32 count;
    s32 i;

    func_080C7B78(source, &state, &first);
    if (state->playing == 0)
        return 1;
    func_080A8DB8(state);
    if (state->current == 0)
        return 1;
    func_0801C960(state->x, state->y, &x, &y);
    if (state->mode > 1) {
        if (owner->entries[state->number].value != state->mode) {
            state->playing = 0;
            return 1;
        }
        if (state->current != 0)
            func_08001F34(state->current, x, y, 0, 0, 0, 0, 0,
                          owner->base + 10 + state->number * 9, 0,
                          state->unknown_1c);
    } else {
        if (state->number == 0) {
            count = 1;
            data_0200F9D0[0] = owner->base;
        } else {
            count = 0;
            for (i = 0; i < 3 && state->digits[i] != 0xff; i++) {
                data_0200F9D0[count] = owner->base + state->digits[i];
                count++;
            }
        }
        x += (3 - count) * 4;
        if (state->current != 0)
            data_08394044(state->current, x, y, 0, 0, 0, 0, 0,
                          data_0200F9D0, 0, state->unknown_1c, count);
    }
    return 1;
}
