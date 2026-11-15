#include "ffta.h"

// 0x080D9488..0x080D9528: 160 bytes.  Starts a scroll effect on one
// background coordinate and advances the command state.

typedef struct {
    u16 state;
    u16 unknown_02;
    u8 unknown_04[0x10];
    u16 background;
    u16 coordinate;
} ScrollCommand;

typedef struct {
    u8 stop_requested;
    u8 unknown_01[3];
    void *object;
    u8 background;
    u8 coordinate;
} ScrollCommandState;

typedef struct {
    u16 *registers[8];
} ScrollRegisters;

typedef struct {
    s16 *shadows[8];
} ScrollShadows;

extern const ScrollRegisters data_08149AD4;
extern const ScrollShadows data_08149AF4;

extern void *func_0800CE08(u32 type, s16 value, u16 *reg);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);

u32 func_080D9488(void *context, ScrollCommand *command,
                  ScrollCommandState *state)
{
    switch (command->state) {
    case 0: {
        ScrollRegisters registers = data_08149AD4;
        ScrollShadows shadows = data_08149AF4;
        u8 index;

        state->background = command->background;
        state->coordinate = command->coordinate;
        index = state->background << 1;
        index |= state->coordinate;
        state->object = func_0800CE08(0, *shadows.shadows[index],
                                      registers.registers[index]);
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100:
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
