typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 flags;
} __attribute__((packed)) Header;

/* 0x080D66F0..0x080D6798: 168 bytes. */
u8 func_080D66F0(const u8 **stream, u16 *index, u8 encoded)
{
    u8 result;

    if (encoded) {
        const u8 *data = *stream;
        u32 header = ((const Header *)data)->flags;
        u32 length = header & 0x3FFF;
        u32 mode = 0;

        if (header & 0x8000) {
            mode = 1;
            result = *index + data[2];
        } else {
            if (header & 0x4000) {
                mode = 2;
                result = data[2];
            } else {
                result = data[2 + *index];
            }
        }

        if (++*index == length) {
            if (mode) {
                *stream = data + 4;
            } else {
                if (length & 1)
                    length++;
                *stream = data + 2 + length;
            }
            *index = 0;
        }
    } else {
        const u8 *data = *stream;

        result = data[*index];
        (*index)++;
    }
    return result;
}
