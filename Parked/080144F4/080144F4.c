#include "ffta.h"

// Complete [0x080144F4, 0x08014778): 644 bytes, 131 instructions,
// including the 89-entry inline jump table for the '@' control codes.

typedef struct {
    u8 unknown_00[0x13];
    u8 mode;
} State080144F4;

extern State080144F4 g_state_020020D0;

extern u8 func_08018CEC(u8 *destination, u8 code);
extern u16 func_0801624C(u8 *destination, u8 index);
extern u16 func_0801446C(const u8 *data, u16 *total);
extern u16 func_08013A5C(u16 index);
extern u16 func_08013BC0(u16 value, u16 multiple);

u16 func_080144F4(const u8 *string, u8 align)
{
    const u8 *text = string;
    u8 name[0x2C];
    u8 label[0x2C];
    u16 width;
    u16 widest = 0;
    int done;
    u8 code;

    do {
        width = 0;
        done = 0;
        while (*text != 0) {
            if (*text == 0x40) {
                code = text[1];
                text += 2;
                switch (code) {
                case 0x73:
                    width += g_state_020020D0.mode != 0 ? 0x10 : 6;
                    break;
                case 0x63:
                case 0x6E:
                    done = 1;
                    break;
                case 0x25:
                    func_08018CEC(name, *text);
                    width += func_080144F4(name, 0);
                    text++;
                    break;
                case 0x66:
                    text += 2;
                    break;
                case 0x72:
                    func_0801624C(label, *text);
                    width += func_080144F4(label, 0);
                    text++;
                    break;
                case 0x67:
                    width += 0x10;
                    text++;
                    break;
                case 0x3C:
                    width -= *text;
                    text++;
                    break;
                case 0x3E:
                    width += *text;
                    text++;
                    break;
                case 0x21:
                case 0x6C:
                case 0x74:
                    text++;
                    break;
                case 0x53:
                    text -= 2;
                    text += func_0801446C(text, &width);
                    break;
                case 0x61:
                case 0x62:
                case 0x6B:
                case 0x70:
                case 0x75:
                case 0x77:
                case 0x78:
                case 0x79:
                    break;
                }
                if (done == 1)
                    break;
            } else {
                width += func_08013A5C(((text[0] << 8) | text[1]) & 0x7FFF);
                text += 2;
            }
        }
        if (widest < width)
            widest = width;
    } while (*text != 0);

    return align != 0 ? func_08013BC0(widest, 8) : widest;
}
