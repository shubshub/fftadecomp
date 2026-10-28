#include "ffta.h"

typedef struct Decoder Decoder;
struct Decoder {
    const u8 *input;
    u8 *output;
    void *context;
    u32 length;
    u32 distance;
    void (*handler)(Decoder *decoder);
};

extern void func_08022748(Decoder *decoder);
extern void func_08022770(Decoder *decoder);
extern void func_08022794(Decoder *decoder);
extern void func_080227BC(Decoder *decoder);

/* Complete target: [0x08022298, 0x080223B2), 282 bytes. */
void func_08022298(Decoder *decoder, u8 *output, const u8 *input, void *context)
{
    const u8 *cursor;
    u16 header;
    void (*handler)(Decoder *decoder);

    decoder->input = input;
    decoder->output = output;
    decoder->context = context;
    cursor = decoder->input;
    header = *cursor;

    if (header & 0x80)
    {
        u16 distance;

        decoder->length = ((header & 0x7F) >> 2) + 3;
        cursor++;
        distance = (header & 1) ? (u16)(*cursor | 0x100) : (u16)*cursor;
        decoder->distance = ((header & 2) ? distance | 0x200 : distance) + 1;
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

        cursor++;
        next = *cursor;

        decoder->length = ((header & 0xF) | ((next >> 2) & 0xF0)) + 4;
        cursor++;
        decoder->distance = (((next & 0x3F) << 8) | *cursor) + 1;
        cursor++;
        decoder->input = cursor;
        handler = func_08022748;
    }
    else if (header == 2)
    {
        cursor++;
        decoder->length = *cursor + 3;
        cursor++;
        decoder->input = cursor;
        handler = func_08022770;
    }
    else if (header == 0)
    {
        cursor++;
        decoder->length = *cursor + 5;
        cursor++;
        decoder->distance = (*(const u16 *)cursor + 1) & 0xFFFF;
        cursor += 2;
        decoder->input = cursor;
        handler = func_08022748;
    }
    else if (header == 1)
    {
        decoder->length = ((const u8 *)input)[1] + 3;
        decoder->input = (const u8 *)input + 2;
        handler = func_08022794;
    }
    else
        handler = 0;

    decoder->handler = handler;
}
