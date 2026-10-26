typedef unsigned char u8;

u8 func_080CDCD4(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xED;
    u8 mask = 0x20;
    int value = *flags;

    if (!(value & mask))
        return 0;
    return 1;
}
