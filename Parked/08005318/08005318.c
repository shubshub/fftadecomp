#include "ffta.h"

extern u8 *data_03002BB8;
extern s32 data_03002BB4;
extern u32 data_03002BB0;
extern s32 func_080051C4(const u8 *entry, const u8 *dictionary);

/* Target: complete [0x08005318, 0x080053D4), 188 bytes. */
s32 func_08005318(const void *data, u8 *output, u16 start, u16 count)
{
    const u8 *source = data;
    u16 total = (source[2] << 8) | source[3];
    u16 first;
    const u8 *bytes;
    const u8 *dictionary;
    u32 offset;

    if (start >= total)
        return 1;
    if (count > total || count == 0)
        count = total;
    if (start + count > total)
        count = total - start;

    first = start;
    bytes = source + 4;
    offset = (bytes[0] << 24) | (bytes[1] << 16)
           | (bytes[2] << 8) | bytes[3];
    dictionary = source + offset;

    data_03002BB4 = -1;
    data_03002BB8 = output;
    *output = 0;
    data_03002BB0 = 0;

    for (; start < count + first; start++)
    {
        const u8 *entry = source + (start * 4 + 8);
        u32 entryOffset = (entry[0] << 24) | (entry[1] << 16)
                        | (entry[2] << 8) | entry[3];
        if (!func_080051C4(source + entryOffset, dictionary))
            return 1;
    }
    return 0;
}
