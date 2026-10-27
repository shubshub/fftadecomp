#include "ffta.h"

typedef struct TextState TextState;

extern void func_08013528(TextState *state);
extern u16 func_08014778(const u8 *text);
extern void func_08013728(TextState *state, s16 amount);
extern u16 func_08015110(TextState *state, void *buffer, const u8 *text,
                         u8 style, u8 mode);

static inline s16 centered_text_offset(const u8 *text, u8 width)
{
    u16 text_width = func_08014778(text);

    return (width * 8 - text_width) / 2;
}

/* Complete target: 0x0801539C..0x080153FC, 96 bytes. */
u16 func_0801539C(TextState *state, void *buffer, const u8 *text,
                   u8 style, u8 width)
{
    s16 offset;

    func_08013528(state);
    offset = centered_text_offset(text, width);
    func_08013728(state, offset);
    return func_08015110(state, buffer, text, style, 0);
}
