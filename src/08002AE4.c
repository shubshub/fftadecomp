#include "ffta.h"

static inline u8 is_ascii_letter(u8 character)
{
    if ((character >= 'a' && character <= 'z') ||
        (character >= 'A' && character <= 'Z'))
        return 1;
    return 0;
}

static inline u8 is_ascii_control(u8 character)
{
    if (character <= 0x1F || character == 0x7F)
        return 1;
    return 0;
}

int func_08002AE4(u8 character)
{
    if (is_ascii_letter(character) || is_ascii_control(character))
        return 0;
    return 1;
}
