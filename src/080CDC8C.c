typedef unsigned char u8;

u8 func_080CDC8C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xED;
    u8 mask = 4;
    int value = *flags;

    if (!(value & mask))
        return 0;
    return 1;
}
