#include "ffta.h"

// Complete [0x08126764, 0x0812682C): 200 bytes, 100 instructions,
// including two literal pools.

typedef struct {
    void *object;
    u8 unknown_04[0x1A];
    u8 palette;
} Subject;

typedef struct {
    Subject *subject;
    u8 duration;
    u8 palette;
    u8 mode;
    u8 percentage;
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
extern const u16 *func_080CBA3C(u8 index);
extern PaletteTransition *func_08147D2C(u16 start, u16 count, u16 duration,
                                        const u16 *source);

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

PaletteTransition *func_08126764(PaletteState *state)
{
    u8 output;
    u8 source;

    func_08022238(state->subject->object, &output);
    state->palette = ClaimPalette(state->subject->palette);
    source = output;

    switch (state->mode) {
    case 0:
        data_0836D4BC[0](state->colors, &data_03003A60[source * 16],
                         sizeof(state->colors));
        break;
    case 1:
        data_0836D4BC[0](&data_03003A60[state->palette * 16],
                         &data_03003A60[source * 16], sizeof(state->colors));
        data_0836D4BC[0](state->colors, func_080CBA3C(15),
                         sizeof(state->colors));
        break;
    }
    return func_08147D2C(state->palette * 16 + 0x100, 16, state->duration,
                         state->colors);
}
