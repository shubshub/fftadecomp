#include "ffta.h"

typedef struct {
    void *object;
    u16 duration;
    u8 palette;
} PaletteSettings;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    const PaletteSettings *settings;
    u8 unknown_08[0x0C];
    u16 delay;
} PaletteTask;

typedef struct {
    void *object;
    u16 duration;
    u8 palette;
    u8 unknown_07;
    u16 delay;
    u8 unknown_0A[2];
    void *effect;
} PaletteState;

extern u16 data_03003A60[];
extern u8 func_080DBC18(void *object, u8 palette);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void *func_08147D2C(u16 offset, u32 count, u16 duration, u16 *colors);
extern void *func_081484CC(void *effect);

u32 func_080DB774(void *object, PaletteTask *task, PaletteState *state)
{
    switch (task->state) {
    case 0:
        {
            const PaletteSettings *settings = task->settings;

            state->object = settings->object;
            state->duration = settings->duration;
            state->palette = settings->palette;
            state->delay = task->delay;
        }
        break;
    case 1:
        break;
    case 0x100:
        if (state->delay) {
            state->delay--;
            if (state->delay)
                break;
        }
        if (state->duration == 0) {
            func_080DBC18(state->object, 15);
            task->state = 2;
        }
        {
            u8 source = func_080DBC18(state->object, state->palette);
            u16 *palettes = data_03003A60;

            func_0814186C(palettes + source * 16,
                          palettes + state->palette * 16, 16);
            state->effect = func_08147D2C(0x101 + (state->palette << 4),
                                         15, state->duration, palettes + 0xF1);
        }
        task->state++;
        break;
    case 0x101:
        state->effect = func_081484CC(state->effect);
        if (state->effect == 0) {
            func_080DBC18(state->object, 15);
            task->state = 2;
        }
        break;
    }
    return 0;
}
