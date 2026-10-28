typedef unsigned char u8;

/* 0x080D37F8..0x080D3818: 32 bytes. */
extern u8 func_080D3970(void);
extern u8 func_080D39B0(void);

u8 func_080D37F8(void)
{
    if (!func_080D3970())
        return 0;
    if (!func_080D39B0())
        return 0;
    return 1;
}
