#include "ffta.h"

typedef struct Decoder Decoder;
typedef u32 (*DecoderHandler)(Decoder *decoder);

struct Decoder {
    const u8 *input;
    u8 *output;
    s32 remaining;
    u32 length;
    u32 distance;
    DecoderHandler handler;
};

extern u32 func_08022748(Decoder *decoder);
extern u32 func_08022770(Decoder *decoder);
extern u32 func_08022794(Decoder *decoder);
extern u32 func_080227BC(Decoder *decoder);

/* Complete [0x08022298, 0x080223B2): 282 bytes, 129 instructions.
 * Starts a decoder on a compressed stream and decodes its first token. */
void func_08022298(Decoder *decoder, u8 *output, const u8 *input, s32 size)
{
    const u8 *cursor;
    u32 *distance;
    u8 header;
    DecoderHandler handler;

    decoder->input = input;
    decoder->output = output;
    decoder->remaining = size;

    cursor = decoder->input;
    /* The ROM forms decoder + 0x10 ahead of the header read (0x080222A4) and
     * the 0x80 token stores through it (0x080222EC).  The same token decoder
     * at 0x080223DA and 0x080224F6 forms it at the same point. */
    distance = &decoder->distance;
    header = *cursor;

    if (header & 0x80)
    {
        u16 offset;

        decoder->length = ((header & 0x7F) >> 2) + 3;
        offset = *++cursor;
        offset |= (header & 1) ? 0x100 : 0;
        offset |= (header & 2) ? 0x200 : 0;
        *distance = offset + 1;
        cursor++;
        decoder->input = cursor;
        handler = func_08022748;
    }
    else if (header & 0x40)
    {
        decoder->length = (header & 0x3F) + 1;
        cursor++;
        decoder->input = cursor;
        handler = func_080227BC;
    }
    else if (header & 0x20)
    {
        decoder->length = (header & 0x1F) + 2;
        cursor++;
        decoder->input = cursor;
        handler = func_08022770;
    }
    else if (header & 0x10)
    {
        u32 next;

        next = *++cursor;
        decoder->length = ((header & 0xF) | ((next >> 2) & 0xF0)) + 4;
        *distance = (((next & 0x3F) << 8) | *++cursor) + 1;
        cursor++;
        decoder->input = cursor;
        handler = func_08022748;
    }
    else if (header == 2)
    {
        decoder->length = *++cursor + 3;
        cursor++;
        decoder->input = cursor;
        handler = func_08022770;
    }
    else if (header == 0)
    {
        decoder->length = *++cursor + 5;
        cursor++;
        *distance = (*(const u16 *)cursor + 1) & 0xFFFF;
        cursor += 2;
        decoder->input = cursor;
        handler = func_08022748;
    }
    else if (header == 1)
    {
        decoder->length = cursor[1] + 3;
        cursor += 2;
        decoder->input = cursor;
        handler = func_08022794;
    }
    else
        handler = 0;

    decoder->handler = handler;
}
