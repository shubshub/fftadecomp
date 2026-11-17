// Complete [0x08015110,0x0801539C): 652 bytes, 326 instructions.
// Draws a text script: glyph pairs, raw bytes after 0x01, and '@' escapes.
#include "ffta.h"

typedef struct TextState {
    u8 unknown_00[4];
    void *destination;
} TextState;

extern u8 data_02003CB0[];

extern void func_08013528(TextState *state, const void *source);
extern void func_080137C0(TextState *state, u8 style);
extern void func_0801360C(TextState *state, s32 character);
extern void func_08013728(TextState *state, s32 amount);
extern u8 func_08018CEC(u8 *destination, u8 code);
extern u8 func_08015DAC(void *destination, u8 code, u8 *missing);
extern void func_0814186C(const void *source, void *destination, u32 control);

u16 func_08015110(TextState *state, void *buffer, const u8 *text,
                  u8 style, u8 mode)
{
    const u8 *p = text;
    u8 raw = 0;
    const u8 *resume = 0;
    u8 done = 0;
    u8 name[0x2C];
    u8 c;

    if (mode)
        func_08013528(state, buffer);
    func_080137C0(state, style);

    for (;;) {
        c = *p;
        if (c == 1) {
            raw = 1;
            p++;
            continue;
        }
        if (c == 0) {
            if (resume) {
                p = resume;
                resume = 0;
                continue;
            }
            p++;
            break;
        }
        if (!raw) {
            if (c & 0x80) {
                func_0801360C(state, (u16)((c << 8) | p[1]) & 0x7FFF);
                p += 2;
            } else if (c == '@') {
                switch (p[1]) {
                case 'c':
                case 'n':
                    p += 2;
                    done = 1;
                    break;
                case 's':
                    func_08013728(state, 6);
                    p += 2;
                    break;
                case '<':
                    func_08013728(state, -p[2]);
                    p += 3;
                    break;
                case '>':
                    func_08013728(state, p[2]);
                    p += 3;
                    break;
                case '!':
                case 't':
                    p += 3;
                    break;
                case '%':
                    func_08018CEC(name, p[2]);
                    p += 3;
                    resume = p;
                    p = name;
                    break;
                case 'g':
                    {
                        u8 missing = 0;

                        func_08015DAC(data_02003CB0, p[2], &missing);
                        if (!missing) {
                            func_0814186C(data_02003CB0, state->destination,
                                          0x40);
                            func_08013728(state, 16);
                        }
                        p += 3;
                    }
                    break;
                case 'u':
                case 'x':
                    p += 2;
                    break;
                }
            }
        } else {
            func_0801360C(state, c - 1);
            p++;
        }
        if (done)
            break;
    }
    return p - text;
}
