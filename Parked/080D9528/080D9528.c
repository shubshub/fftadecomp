#include "ffta.h"

// Complete target: [0x080D9528, 0x080D963A), 274 bytes, including the
// literal pool.

typedef struct {
    u16 *registers[8];
} ScrollRegisters;

typedef struct {
    s16 *shadows[8];
} ScrollShadows;

typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    u16 layer;
    u16 axis;
    u16 mode;
} ScrollCommand;

typedef struct {
    u8 active;
    u8 unknown_01[3];
    void *object;
    u8 mode;
    u8 layer;
    u8 axis;
} ScrollCommandState;

extern const ScrollRegisters data_08149AD4;
extern const ScrollShadows data_08149AF4;
extern void *func_0800CE08(u8 mode, s16 value, u16 *reg);
extern void *func_0800DA48(void *object, u8 mode, u8 index);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);

u32 func_080D9528(void *task, ScrollCommand *command, ScrollCommandState *state)
{
    switch (command->state) {
    case 0: {
        ScrollRegisters registers = data_08149AD4;
        ScrollShadows shadows = data_08149AF4;
        s16 *shadow;
        u8 index;
        u8 count;
        u8 i;
        u16 fill;

        state->layer = command->layer;
        state->axis = command->axis;
        state->mode = command->mode;
        index = state->layer << 1;
        index |= state->axis;
        shadow = shadows.shadows[index];
        state->object = func_0800CE08(state->mode, *shadow,
                                      registers.registers[index]);
        if (state->mode == 0)
            break;
        count = 1;
        if (state->mode == 2)
            count = 3;
        for (i = 0; i < count; i++) {
            u8 part;
            void *destination;

            if (state->mode == 1)
                part = 1;
            else if (i == 0)
                part = 1;
            else if (i == 1)
                part = 2;
            else
                part = 3;
            destination = func_0800DA48(state->object, state->mode, part);
            fill = *shadows.shadows[index + i + 1];
            func_0814186C(&fill, destination, 0x010000A0);
        }
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100:
        if (state->active) {
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
