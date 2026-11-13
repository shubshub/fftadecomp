// Target: 0x08014F10-0x080150D2, 450 complete bytes (jump table at 0x08014F44).
typedef unsigned char u8;

u8 *func_08014F10(u8 *s, u8 c)
{
    u8 *p = s;
    int n;

    while (*p != 0) {
        if (*p != 0x40) {
            p += 2;
            continue;
        }
        if (p[1] == c) {
            return p;
        }
        switch (p[1]) {
        case 0x21:
        case 0x25:
        case 0x3C:
        case 0x3E:
        case 0x67:
        case 0x6C:
        case 0x72:
        case 0x74:
            p += 3;
            break;
        case 0x66:
            p += 4;
            break;
        case 0x53:
            for (n = 0; n < 2; n++) {
                while (*p++ != 0)
                    continue;
            }
            break;
        case 0x61:
        case 0x62:
        case 0x6B:
        case 0x6E:
        case 0x70:
        case 0x73:
        case 0x75:
        case 0x77:
        case 0x78:
            p += 2;
            break;
        case 0x63:
            return 0;
        }
    }
    return 0;
}
