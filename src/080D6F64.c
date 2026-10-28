typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* 0x080D6F64: 86 bytes. Expand four packed two-bit values into nibbles. */
void func_080D6F64(const u8 *source, u16 count, u8 *destination)
{
    u8 value;
    u16 i;
    u16 j;

    for (i = 0; i < count; i++) {
        value = source[i];
        *destination = 0;
        for (j = 0; j < 4; j++) {
            u8 bits = value & 3;

            if (j & 1) {
                bits <<= 4;
                *destination |= bits;
                destination++;
                *destination = 0;
            } else {
                *destination |= bits;
            }
            value >>= 2;
        }
    }
}
