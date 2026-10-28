#include "ffta.h"

/* 080150D4..0801510E: 58 bytes. */
u8 func_080150D4(const u8 *text)
{
    if (text[0] == '@') {
        switch (text[1]) {
        case '!':
        case '%':
        case 'g':
        case 'l':
        case 'r':
        case 't':
            return text[2];
        }
    }
    return 0xFF;
}
