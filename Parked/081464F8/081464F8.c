#include "ffta.h"

typedef union {
    u32 word;
    u8 bytes[4];
} PackedWord;

typedef struct {
    u8 unknown_00[0x28];
    u32 value;
    u8 unknown_2C[0x14];
    const u8 *cursor;
} CommandContext;

/* Complete [0x081464F8, 0x08146540): 72 bytes, 27 instructions.
 * 10b50a6c0c48044010780443507803020a4804401c4390780304094804401c43
 * d0780306074804401c438c6204320a6410bc01bc0047000000ffffffff00ffff
 * ffff00ffffffff00
 */
void func_081464F8(void *owner, CommandContext *context)
{
    PackedWord value;

    value.bytes[0] = context->cursor[0];
    value.bytes[1] = context->cursor[1];
    value.bytes[2] = context->cursor[2];
    value.bytes[3] = context->cursor[3];
    context->value = value.word;
    context->cursor += 4;
}
