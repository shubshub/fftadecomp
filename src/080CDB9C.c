typedef unsigned char u8;

u8 func_080CDB9C(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEB;
    u8 mask = 0x80;
    int value = *flags;

    if (!(value & mask))
        return 0;
    return 1;
}
