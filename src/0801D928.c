/* Target: 16 bytes. Read bit 1 of the state halfword at 0x2C. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801D928(void)
{
    return (g_state_02007F40[0x16] >> 1) & 1;
}
