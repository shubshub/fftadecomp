#include "ffta.h"

// Complete [0x081265B8, 0x08126764): 428 bytes, 173 instructions,
// including five literal pools.

typedef struct {
    void *object;
    u8 unknown_04[0x1A];
    u8 palette;
} Subject;

typedef struct {
    Subject *subject;
    u8 duration;
    u8 palette;
    u8 from;
    u8 to;
    u16 colors[16];
} PaletteState;

typedef struct {
    u8 unknown_00;
    u8 palette;
    u8 unknown_02[6];
} PaletteSlot;

typedef struct PaletteTransition PaletteTransition;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier data_0836D4BC[];
extern u16 data_03003A60[];
extern u16 func_08022238(void *object, u8 *output);
extern PaletteSlot *func_08121C98(u8 index);
extern void func_0814835C(u16 *destination, u16 value, u16 count);
extern void func_08148104(const u16 *source, u16 *destination, u16 count,
                          u16 level);
extern PaletteTransition *func_08147A7C(u16 start, u16 count, u16 duration);
extern PaletteTransition *func_08147AD0(u16 start, u16 count, u16 duration);
extern PaletteTransition *func_08147D2C(u16 start, u16 count, u16 duration,
                                        const u16 *source);

/* An inlined copy of the claim loop in func_08126764 (src/08126764.c): the
 * ROM repeats it instruction for instruction at 0x081265C8-0x081265F6 and
 * 0x08126774-0x081267A2. */
static inline u8 ClaimPalette(u8 previous)
{
    s32 i;

    for (i = 0; i <= 6; i++) {
        PaletteSlot *slot = func_08121C98(i);

        if (slot->palette) {
            if (slot->palette == previous)
                return slot->palette;
        } else {
            slot->palette = 12 - i;
            return slot->palette;
        }
    }
    return 12;
}

PaletteTransition *func_081265B8(PaletteState *state)
{
    u8 output;
    u8 source;

    func_08022238(state->subject->object, &output);
    state->palette = ClaimPalette(state->subject->palette);
    source = output;

    if (state->from == 0 && state->to == 100) {
        u16 *target = &data_03003A60[state->palette * 16];
        data_0836D4BC[0](state->colors, &data_03003A60[source * 16],
                         sizeof(state->colors));
        func_0814835C(target, 0, 16);
        return func_08147D2C(state->palette * 16 + 0x100, 16, state->duration,
                             state->colors);
    } else if (state->from == 100 && state->to == 0) {
        data_0836D4BC[0](&data_03003A60[state->palette * 16],
                         &data_03003A60[source * 16], sizeof(state->colors));
        return func_08147A7C(state->palette * 16 + 0x100, 16, state->duration);
    } else if (state->from == 100 && state->to == 200) {
        data_0836D4BC[0](&data_03003A60[state->palette * 16],
                         &data_03003A60[source * 16], sizeof(state->colors));
        return func_08147AD0(state->palette * 16 + 0x100, 16, state->duration);
    } else if (state->from == 200 && state->to == 100) {
        u16 *target = &data_03003A60[state->palette * 16];
        data_0836D4BC[0](state->colors, &data_03003A60[source * 16],
                         sizeof(state->colors));
        func_0814835C(target, 0x7FFF, 16);
        return func_08147D2C(state->palette * 16 + 0x100, 16, state->duration,
                             state->colors);
    } else {
        /* Unsigned quotients: bl __udivsi3 (func_08142AB0) at 0x081266C4
         * and 0x081266E2. */
        func_08148104(&data_03003A60[source * 16],
                      &data_03003A60[state->palette * 16], 16,
                      (state->from << 8) / 100u);
        func_08148104(&data_03003A60[source * 16], state->colors, 16,
                      (state->to << 8) / 100u);
        return func_08147D2C(state->palette * 16 + 0x100, 16, state->duration,
                             state->colors);
    }
}
