int func_08002A78(unsigned char value)
{
    if (value <= 0x1F || value == 0x7F)
        return 1;
    return 0;
}
