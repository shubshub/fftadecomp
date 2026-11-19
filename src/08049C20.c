/* 0x08049C20-0x08049C22: 2 bytes, 70 47 (bx lr); a zero halfword pads to the
 * next function at 0x08049C24. No word-aligned reference to 0x08049C20 or
 * 0x08049C21 and no Thumb BL to 0x08049C20 exists in the ROM image. */
void func_08049C20(void)
{
}
