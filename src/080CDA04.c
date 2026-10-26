typedef unsigned char u8;

u8 func_080CDA04(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE9;
    u8 mask = 0x80;

    if (!(*flags & mask))
        return 0;
    return 1;
}
