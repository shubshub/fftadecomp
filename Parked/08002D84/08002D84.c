#include "ffta.h"

/* 0x08002D84 - 32 bytes.
 * Target: 00b50006010e0a1c081c61380006000e192801d80a1c203a1006000e02bc0847
 */
u8 func_08002D84(u8 character)
{
    u8 result = character;

    if (character >= 'a' && character <= 'z')
        result = character - ('a' - 'A');
    return result;
}
