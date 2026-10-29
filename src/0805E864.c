#include "ffta.h"

typedef struct {
    u8 unknown_00[0x16];
    u16 identifier;
} SelectionEntry;

typedef struct {
    u8 unknown_00[0x1199];
    u8 mode;
    u8 unknown_119A;
    u8 phase;
    u8 unknown_119C;
    u8 flag;
    u8 unknown_119E[0x4E];
    SelectionEntry *entries[153];
    const u8 *identifier;
    SelectionEntry *selected;
} State;

extern State *data_0200F448;
extern u8 func_08060DD4(void);
extern s16 func_08060DC4(void);
extern u8 func_0805D1C0(u32 enabled);

/* 0x0805E864..0x0805E924 - 192 bytes including literal pools. */
void func_0805E864(void)
{
    const u8 *identifier;
    u32 identifier_low;
    u32 identifier_high;

    switch (func_08060DD4()) {
    case 3:
    case 4:
        data_0200F448->selected = data_0200F448->entries[func_08060DC4()];
        identifier = data_0200F448->identifier;
        identifier_low = identifier[0];
        identifier_high = identifier[1];
        identifier_high &= 3;
        data_0200F448->selected->identifier =
            (identifier_high << 8) | identifier_low;
        data_0200F448->flag = func_0805D1C0(1);
        data_0200F448->phase = 9;
        data_0200F448->mode = 18;
        break;
    case 1:
    case 2:
        if (data_0200F448->selected != 0)
            data_0200F448->selected->identifier = 0;
        data_0200F448->phase = 5;
        data_0200F448->mode = 19;
        break;
    }
}
