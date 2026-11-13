#include "ffta.h"

// Complete [0x080D9170, 0x080D934E): 478 bytes, 239 instructions.
typedef struct LineState {
    s32 x, y, endX, endY;
    s32 stepX, stepY, deltaX, deltaY;
    s32 accumulator, error, remaining;
} LineState;

typedef struct {
    u8 column;
    u8 count;
    s16 offset;
    u16 duration;
    u16 unknown_06;
} Slot;

typedef struct {
    u8 kind;
    u8 unknown_01[3];
    void *object;
    u8 first;
    u8 second;
    u8 count;
    u8 unknown_0b;
    LineState lines[8];
    Slot slots[8];
} Payload;

typedef struct {
    u16 phase;
    u16 unknown_02;
    const Slot *slots;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u16 count;
} Descriptor;

typedef struct { u32 values[8]; } Values;
typedef struct { const s16 *pointers[8]; } Pointers;

extern const Values data_08149AD4;
extern const Pointers data_08149AF4;

extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);
extern void *func_0800CE08(u32, s32, u32);
extern void func_080075CC(LineState *, s32, s32, s32, s32);
extern void func_080076A0(LineState *);
extern u32 func_08007880(const LineState *);
extern void func_0800D95C(void *, u8, u8, u8, u8, s16);

u32 func_080D9170(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        const Slot *source = descriptor->slots;
        u8 i;

        payload->first = descriptor->first;
        payload->second = descriptor->second;
        payload->count = descriptor->count;
        for (i = 0; i < payload->count; i++) {
            payload->slots[i].column = source[i].column;
            payload->slots[i].count = source[i].count;
            payload->slots[i].offset = source[i].offset;
            payload->slots[i].duration = source[i].duration;
        }
        break;
    }
    case 1:
        func_0800C668(payload->object);
        break;
    case 0x100: {
        Values values = data_08149AD4;
        Pointers pointers = data_08149AF4;
        u8 row = payload->first << 1;
        u32 index = row | payload->second;
        s32 base = *pointers.pointers[index];
        u8 i;

        payload->object = func_0800CE08(0, base, values.values[index]);
        for (i = 0; i < payload->count; i++)
            func_080075CC(&payload->lines[i], base, 0,
                base + payload->slots[i].offset,
                payload->slots[i].duration - 1);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        u8 i;

        for (i = 0; i < payload->count; i++) {
            Slot *slot = &payload->slots[i];

            func_080076A0(&payload->lines[i]);
            if (func_08007880(&payload->lines[i]))
                func_080075CC(&payload->lines[i], (s16)payload->lines[i].x, 0,
                    (s16)payload->lines[i].x + slot->offset, slot->duration - 1);
            func_0800D95C(payload->object, 0, 0, slot->column, slot->count,
                (s16)payload->lines[i].x);
        }
        if (payload->kind != 0) {
            func_0800C6C0(payload->object);
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
