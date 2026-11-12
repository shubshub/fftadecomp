/* Target: 08001CD0-08001CDF, 16 bytes including the data literal. */
extern unsigned char data_03000028;

void func_08001CD0(void)
{
    data_03000028 ^= 1;
}
