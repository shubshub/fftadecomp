#include "ffta.h"

// Complete target: [0x0812AAC8, 0x0812AC08), 320 bytes.

typedef struct {
    u8 unknown_000[0x2F6];
    u8 record;
    u8 unknown_2F7[0x310 - 0x2F7];
    u8 index;
    u8 group;
    u8 name[20];
    u8 length;
} NameEntry;

typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
} InputState;

extern InputState data_03000000;

extern void func_080023D0(InputState *input);
extern void func_08141540(u32 sound);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_0812B538(NameEntry *state, u8 record, u8 index, u8 group);
extern u16 func_0812B184(NameEntry *state);
extern void func_0812AE8C(NameEntry *state);

void func_0812AAC8(NameEntry *state)
{
    u8 saved[20];

    if (data_03000000.pressed & 1) {
        u16 glyph;

        func_080023D0(&data_03000000);
        func_08141540(0x64);
        func_0814186C(state->name, saved, 10);
        glyph = func_0812B538(state, state->record, state->index, state->group);
        state->name[state->length * 2] = glyph >> 8;
        state->name[state->length * 2 + 1] = glyph;
        state->length++;
        glyph = func_0812B184(state);
        state->length--;
        if (glyph > 0x57)
            func_0814186C(saved, state->name, 10);
        else if (state->length < 8)
            state->length++;
        func_0812AE8C(state);
    } else if (data_03000000.pressed & 2) {
        func_080023D0(&data_03000000);
        func_08141540(0x68);
        if (state->length == 8
            && (state->name[state->length * 2] != 0x40
                || state->name[state->length * 2 + 1] != 0x73)) {
            state->name[state->length * 2] = 0x40;
            state->name[state->length * 2 + 1] = 0x73;
        } else {
            if (state->length != 0)
                state->length--;
            state->name[state->length * 2] = 0x40;
            state->name[state->length * 2 + 1] = 0x73;
        }
        func_0812AE8C(state);
    }
}
