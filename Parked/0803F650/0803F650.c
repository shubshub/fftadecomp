#include "ffta.h"

/* Target: complete [0x0803F650, 0x0803F6F8), 168 bytes. */
typedef struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 unknown_06;
    u8 *text;
    u16 field_0c;
    u8 unknown_0e[6];
} TextSegment;

typedef struct {
    u32 mode;
    void *task;
    u32 unknown_08;
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 value;
    u8 field_12;
    u8 unknown_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    TextSegment *segments;
    u8 unknown_1c[0x214];
    TextSegment text[2];
} PanelState;

extern u8 data_0201F4A0[];
extern const u8 data_084B64A4[];
extern u8 data_02003CB0[];
extern u16 func_08013E9C(u8 *destination, const u8 *table,
                          u8 *workspace, u16 index, u32 mode, u32 value);

void func_0803F650(PanelState *state, u16 index)
{
    TextSegment *segments = state->text;
    u8 *text;
    s32 i;

    state->segments = segments;
    state->task = 0;
    state->x = 0;
    state->y = 0;
    state->width = 16;
    state->height = 7;
    state->value = 0x1db;
    state->field_12 = 0;
    state->field_14 = 0;
    state->field_16 = 16;
    state->field_17 = 0;
    state->mode = 2;
    text = data_0201F4A0;
    func_08013E9C(text, data_084B64A4, data_02003CB0, index, 0, 0);
    segments[0].field_00 = 0;
    segments[0].field_02 = 1;
    segments[0].field_04 = 0;
    segments[0].text = text;
    segments[0].field_0c = 0;
    for (i = 0; i < 100; i++) {
        if (data_0201F4A0[i] == '@' && data_0201F4A0[i + 1] == 'c') {
            text = data_0201F4A0 + i + 2;
            break;
        }
    }
    segments[1].field_00 = 1;
    segments[1].field_02 = 1;
    segments[1].field_04 = 1;
    segments[1].text = text;
    segments[1].field_0c = 0;
}
