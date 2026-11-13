// Target 0x080149C0..0x08014B84: complete 452-byte body (jump table inline).
typedef unsigned char u8;
typedef unsigned short u16;

u16 func_080149C0(const u8 *input)
{
    const u8 *text = input;
    int done = 0;
    u16 count = 0;
    while (!done && *text) {
        if (*text != 0x40) {
            count += 2;
            text += 2;
        } else {
            switch (text[1]) {
            case 0x63:
            case 0x6E:
                count += 2;
                done = 1;
                break;
            case 0x61:
            case 0x62:
            case 0x6B:
            case 0x70:
            case 0x73:
            case 0x75:
            case 0x77:
            case 0x78:
            case 0x79:
                count += 2;
                text += 2;
                break;
            case 0x21:
            case 0x25:
            case 0x67:
            case 0x6C:
            case 0x72:
            case 0x74:
                count += 3;
                text += 3;
                break;
            case 0x66:
                count += 4;
                text += 4;
                break;
            }
        }
    }
    return count;
}
