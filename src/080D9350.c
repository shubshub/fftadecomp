#include "ffta.h"

// 0x080D9350..0x080D9488: 312 bytes.  Builds a 160-line scroll table from
// run lengths, hands it to a background-register effect and steps it.

typedef struct {
    u16 *registers[4];
} LineScrollRegisters;

typedef struct {
    u16 delay;
    u16 step;
    const u8 *runs;
} LineScrollSource;

typedef struct {
    u16 state;
    u16 unknown_02;
    const LineScrollSource *source;
    u8 unknown_08[0xC];
    s16 background;
    s16 start;
} LineScrollCommand;

typedef struct {
    u8 stop_requested;
    u8 unknown_01[3];
    void *object;
    u16 timer;
    u16 delay;
    u16 step;
    u16 lines[0xA0];
} LineScrollState;

/* BG0VOFS..BG3VOFS, 0x04000012..0x0400001E. */
extern const LineScrollRegisters data_08149B14;

extern void *func_0800CE08(u32 type, s16 value, u16 *reg);
extern void func_0800D9E0(void *object, u8 mode, u8 row, u8 index, u8 count,
                          const void *source);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);

u32 func_080D9350(void *context, LineScrollCommand *command,
                  LineScrollState *state)
{
    switch (command->state) {
    case 0: {
        LineScrollRegisters registers = data_08149B14;
        const LineScrollSource *source = command->source;
        const u8 *runs;
        u8 line;
        s16 value;

        state->delay = source->delay;
        state->step = source->step;
        state->object = func_0800CE08(0, command->start,
                                      registers.registers[command->background]);
        line = 0;
        value = command->start - 1;
        runs = source->runs;
        do {
            u8 n;

            value++;
            for (n = 0; n < *runs; n++) {
                state->lines[line] = value;
                line++;
                value--;
            }
            runs++;
        } while (line < 0xA0);
        func_0800D9E0(state->object, 0, 0, 0, 0xA0, state->lines);
        state->timer = state->delay;
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100:
        if (state->delay != 0 && --state->timer == 0) {
            u8 line;

            for (line = 0; line < 0xA0; line++)
                state->lines[line] += state->step;
            func_0800D9E0(state->object, 0, 0, 0, 0xA0, state->lines);
            state->timer = state->delay;
        }
        if (state->stop_requested) {
            func_0800C6C0(state->object);
            command->state++;
        }
        break;
    case 0x101:
        command->state = 2;
        break;
    }
    return 0;
}
