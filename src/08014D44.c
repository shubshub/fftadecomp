/* Target 0x08014D44..0x08014F10: complete 460-byte body. */
typedef unsigned char u8;
typedef unsigned short u16;

u16 func_08014D44(const u8 *input, u8 code)
{
    const u8 *text = input;
    u16 count = 0;
    while (*text) {
        if (*text != 0x40) {
            text += 2;
        } else {
            if (text[1] == code)
                count++;
            switch (text[1]) {
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x6B:
            case 0x6E:
            case 0x70:
            case 0x73:
            case 0x75:
            case 0x77:
            case 0x78:
            case 0x79:
                text += 2;
                break;
            case 0x21:
            case 0x25:
            case 0x3C:
            case 0x3E:
            case 0x67:
            case 0x6C:
            case 0x72:
            case 0x74:
                text += 3;
                break;
            case 0x66:
                text += 4;
                break;
            case 0x53:
                {
                int i;
                for (i = 0; i < 2; i++)
                    while (*text++);
            }
                break;
            }
        }
    }
    return count;
}
