#include "ffta.h"

/* Scroll-wave callback, 0x080D8E00..0x080D916E (878 target bytes). */
typedef struct SchedulerDescriptor080D979C {
    u16 phase;
    u16 unknown_02;
    void *value;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u16 third;
} SchedulerDescriptor080D979C;

typedef struct {
    u8 frame_step;
    u8 line_step;
    u8 amplitude;
    u8 phase;
} ScrollWave;

typedef union {
    u16 packed[2];
    struct {
        u8 first;
        u8 last;
        u8 skip_first;
        u8 skip_last;
    } line;
} ScanlineRange;

typedef struct { u16 values[160]; } ScanlineBuffer;

/* A scanline buffer and its control fields fill the spawner's 0x16C-byte payload. */

typedef struct {
    u8 stop_requested;
    u8 unknown_01[3];
    void *object;
    u8 mode;
    u8 background;
    u8 coordinate;
    u8 count;
    u8 frame;
    u8 unknown_0d;
    s16 base[4];
    u8 unknown_16[2];
    ScrollWave waves[4];
    ScanlineRange ranges;
    ScanlineBuffer row;
} ScrollWaveState;

typedef struct { u16 *registers[8]; } ScrollRegisters;
typedef struct { s16 *shadows[8]; } ScrollShadows;
typedef struct { u8 unknown_00[0xC]; u16 flags; } Struct0800C6C0;

extern const ScrollRegisters data_08149AD4;
extern const ScrollShadows data_08149AF4;

s32 func_08007A4C(u8 phase);
void func_0800C668(u8 *object);
void func_0800C6C0(Struct0800C6C0 *object);
void *func_0800CE08(u32 mode, s16 value, u16 *reg);
void func_0800D95C(void *object, u8 mode, u8 row, u8 first, u8 count, s16 value);
void func_0800D9E0(void *object, u8 mode, u8 row, u8 first, u8 count, const void *source);

u32 func_080D8E00(void *task, SchedulerDescriptor080D979C *descriptor,
                  void *payload)
{
    ScrollWaveState *state = payload;

    switch (descriptor->phase) {
    case 0: {
        u8 i;
        u8 count = 0;
        const ScrollWave *source = descriptor->value;

        state->mode = descriptor->first;
        state->background = descriptor->second;
        state->coordinate = descriptor->third;
        if (state->mode == 0)
            count = 1;
        else if (state->mode == 1)
            count = 2;
        else if (state->mode == 2)
            count = 4;
        for (i = 0; i < count; i++) {
            state->waves[i].frame_step = source[i].frame_step;
            state->waves[i].line_step = source[i].line_step;
            state->waves[i].amplitude = source[i].amplitude;
            state->waves[i].phase = source[i].phase;
        }
        state->count = count;
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100: {
        ScrollRegisters registers = data_08149AD4;
        ScrollShadows shadows = data_08149AF4;
        u8 i;
        u8 index = state->background << 1;

        index |= state->coordinate;
        state->object = func_0800CE08(state->mode, *shadows.shadows[index],
                                      registers.registers[index]);
        if (state->base[0] == 0)
            state->base[0] = *shadows.shadows[index];
        for (i = 1; i < state->count; i++) {
            index++;
            func_0800D95C(state->object, state->mode, i, 0, 160,
                          *shadows.shadows[index]);
            state->base[i] = *shadows.shadows[index];
        }
        descriptor->phase++;
        break;
    }
    case 0x101: {
        u8 i;
        u8 last_phase = 0;
        u8 last_amplitude = 0;
        u8 last_step = 0;
        u8 last_base = 0;
        u32 bounded, skip;

        state->frame++;
        bounded = state->ranges.packed[0] != 0;
        skip = state->ranges.packed[1] != 0;
        for (i = 0; i < state->count; i++) {
            ScrollWave *wave = &state->waves[i];
            u8 angle;
            u8 reuse;
            ScanlineBuffer *lines;

            if (!wave->amplitude)
                continue;
            angle = wave->phase;
            reuse = 0;
            if (i != 0 && angle == last_phase && wave->amplitude == last_amplitude
                && wave->line_step == last_step && state->base[i] == last_base)
                reuse = 1;
            lines = &state->row;
            if (!reuse) {
                u16 line = 0;

                if (bounded)
                    line = state->ranges.line.first;
                if (wave->amplitude == 1) {
                    while (line < 160) {
                        s16 value = (s16)func_08007A4C(angle) >> 8;

                        value += state->base[i];
                        lines->values[line] = value;
                        angle += wave->line_step;
                        line++;
                        if (skip && line == state->ranges.line.skip_first)
                            line = state->ranges.line.skip_last + 1;
                        if (bounded && line > state->ranges.line.last)
                            break;
                    }
                } else if (wave->amplitude == 2) {
                    while (line < 160) {
                        s16 value = (s16)func_08007A4C(angle) >> 7;

                        value += state->base[i];
                        lines->values[line] = value;
                        angle += wave->line_step;
                        line++;
                        if (skip && line == state->ranges.line.skip_first)
                            line = state->ranges.line.skip_last + 1;
                        if (bounded && line > state->ranges.line.last)
                            break;
                    }
                } else if (wave->amplitude == 12) {
                    while (line < 160) {
                        s16 value = (s16)func_08007A4C(angle) >> 5;

                        value += value >> 1;
                        value += state->base[i];
                        lines->values[line] = value;
                        angle += wave->line_step;
                        line++;
                        if (skip && line == state->ranges.line.skip_first)
                            line = state->ranges.line.skip_last + 1;
                        if (bounded && line > state->ranges.line.last)
                            break;
                    }
                }
            }
            func_0800D9E0(state->object, state->mode, i, 0, 160, lines);
            last_phase = wave->phase;
            last_step = wave->line_step;
            last_amplitude = wave->amplitude;
            last_base = state->base[i];
            wave->phase += wave->frame_step;
        }
        if (state->stop_requested) {
            func_0800C6C0(state->object);
            descriptor->phase++;
        }
        break;
    }
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
