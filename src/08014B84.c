#include "ffta.h"

// Complete target [0x08014B84, 0x08014D42): 446 bytes, 223 instructions.
u8 *func_08014B84(u8 *text, u8 index)
{
    u8 *p = text;
    u8 count = 0;

    if (index == 0)
        return text;
    while (*p) {
        if (*p != '@') {
            p += 2;
            continue;
        }
        switch (p[1]) {
        case 'a':
        case 'b':
        case 'k':
        case 'n':
        case 'p':
        case 's':
        case 'u':
        case 'w':
        case 'x':
        case 'y':
            p += 2;
            break;
        case 'c':
            p += 2;
            count++;
            if (count == index)
                return p;
            break;
        case '!':
        case '%':
        case '<':
        case '>':
        case 'g':
        case 'l':
        case 'r':
        case 't':
            p += 3;
            break;
        case 'f':
            p += 4;
            break;
        }
    }
    return 0;
}
