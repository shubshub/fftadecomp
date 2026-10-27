#include "ffta.h"

extern u8 data_02007CB0[];

static inline u16 read_u16(const u8 *data)
{
    return data[0] | (data[1] << 8);
}

static inline s32 take_byte(const u8 **stream)
{
    s32 value = **stream;
    (*stream)++;
    return value;
}

void func_0801F098(const u8 *data, const u16 *lookup)
{
    u8 *base = data_02007CB0;

    do {
        u16 offset = read_u16(data);
        u16 *destination = (u16 *)(base + offset);
        s16 i;
        data += 2;

        if (lookup) {
            s32 count = take_byte(&data);
            for (i = 0; i < count; i++) {
                u8 index = take_byte(&data);
                *destination++ = lookup[index];
            }
        } else {
            u16 count = read_u16(data);
            data += 2;
            for (i = 0; i < count / 2; i++) {
                u16 value = read_u16(data);
                data += 2;
                *destination++ = value;
            }
        }
    } while (data[0] | data[1]);
}
