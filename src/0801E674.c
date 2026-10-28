/* Target: 12 bytes. Read the state halfword at offset 8. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801E674(void)
{
    return g_state_02007F40[4];
}
