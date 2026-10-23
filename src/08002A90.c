/* 0x08002A90-0x08002AAA: 26 bytes; external alignment is excluded. */
typedef unsigned char u8;

int func_08002A90(u8 character)
{
    if (character >= '0' && character <= '9')
        return 1;
    return 0;
}
