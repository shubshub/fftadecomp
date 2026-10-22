#include "ffta.h"

void *func_081443FC(void *destination, const void *source, u32 byte_count)
{
    u8 *destination_bytes = destination;
    const u8 *source_bytes = source;

    if (byte_count >= 16 && (((u32)source_bytes | (u32)destination_bytes) & 3) == 0) {
        u32 *destination_words = (u32 *)destination_bytes;
        const u32 *source_words = (const u32 *)source_bytes;

        while (byte_count >= 16) {
            *destination_words++ = *source_words++;
            *destination_words++ = *source_words++;
            *destination_words++ = *source_words++;
            *destination_words++ = *source_words++;
            byte_count -= 16;
        }
        while (byte_count >= 4) {
            *destination_words++ = *source_words++;
            byte_count -= 4;
        }
        destination_bytes = (u8 *)destination_words;
        source_bytes = (const u8 *)source_words;
    }
    while (byte_count--) {
        *destination_bytes++ = *source_bytes++;
    }
    return destination;
}
