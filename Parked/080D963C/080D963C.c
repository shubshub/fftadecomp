#include "ffta.h"

// Complete [0x080D963C, 0x080D96F0), 180 bytes / 90 instructions.
// Start a scanline task on one of two affine background registers and
// fill its 160 line records from a template that steps by 0x100.

typedef struct {
    u32 unknown_00;
    s32 offset;
    u32 unknown_08[3];
} LineRecord;

typedef struct {
    u16 state;
    u16 unknown_02;
    const LineRecord *source;
    u8 unknown_08[0xC];
    s16 background;
} AffineCommand;

typedef struct {
    u8 active;
    u8 unknown_1[3];
    void *object;
} AffineState;

typedef struct {
    u16 *registers[2];
} RegisterPair;

extern const RegisterPair data_08149B24;
extern void func_080D9BC0(void);
extern void *func_0800C3CC(void (*callback)(void), u32 size, u32 type,
                           u16 *destination);
extern LineRecord *func_0800C614(void *task);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);
extern void func_0814186C(const void *source, void *destination, u32 control);

u32 func_080D963C(void *task, AffineCommand *command, AffineState *state)
{
    switch (command->state) {
    case 0: {
        LineRecord record;
        RegisterPair pair = data_08149B24;
        LineRecord *lines;
        u16 i;

        state->object = func_0800C3CC(func_080D9BC0, 0xC80, 0x10,
                                      pair.registers[command->background - 2]);
        lines = func_0800C614(state->object);
        func_0814186C(command->source, &record, 10);
        for (i = 0; i < 160; i++) {
            func_0814186C(&record, lines, 10);
            record.offset += 0x100;
            lines++;
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
