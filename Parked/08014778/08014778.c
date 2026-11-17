#include "ffta.h"

// Complete [0x08014778, 0x080149BE): 582 bytes, with an 89-entry jump table
// for the @-codes 0x21..0x79 at 0x080147E0.
// Measures the pixel width of an encoded text string; @% expands a field
// into a stack buffer and measures it recursively.

typedef struct {
    u8 unknown_00[0x13];
    u8 mode;
} State08014778;

extern State08014778 g_state_020020D0;
extern s32 func_08013A5C(s32 index);
extern u8 func_08018CEC(u8 *destination, u8 code);

u16 func_08014778(const u8 *text)
{
    u8 buffer[0x2C];
    s32 raw = 0;
    s16 width = 0;

    while (*text != 0) {
        if (*text == 1) {
            raw = 1;
        } else if (!raw) {
            if (*text & 0x80) {
                width += func_08013A5C((u16)(text[0] << 8 | text[1]) & 0x7FFF);
                text += 2;
                continue;
            }
            if (*text != 0x40)
                continue;
            switch (text[1]) {
            case 0x73:
                width += g_state_020020D0.mode != 0 ? 0x10 : 6;
                text += 2;
                break;
            case 0x25:
                func_08018CEC(buffer, text[2]);
                width += func_08014778(buffer);
                text += 3;
                break;
            case 0x66:
                text += 4;
                break;
            case 0x67:
                width += 0x10;
                text += 3;
                break;
            case 0x3C:
                width -= text[2];
                text += 3;
                break;
            case 0x3E:
                width += text[2];
                text += 3;
                break;
            case 0x21:
            case 0x6C:
            case 0x74:
                text += 3;
                break;
            case 0x61:
            case 0x62:
            case 0x6B:
            case 0x70:
            case 0x75:
            case 0x77:
            case 0x78:
            case 0x79:
                text += 2;
                break;
            case 0x63:
            case 0x6E:
                return width;
            }
            continue;
        } else {
            width += func_08013A5C(*text - 1);
        }
        text++;
    }
    return width;
}
