/* Target: 16 bytes. Test the cleared high bit of the state halfword at 0x2C. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801AE10(void)
{
    return (g_state_02007F40[0x16] >> 15) ^ 1;
}
