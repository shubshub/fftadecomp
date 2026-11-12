/* 0x08001CE0-0x08001CF0: 16 bytes, including the referenced data literal.
 * Target: 02 48 01 78 01 22 51 40 01 70 70 47 58 2F 00 03
 */
extern unsigned char data_03002F58;

void func_08001CE0(void)
{
    data_03002F58 ^= 1;
}
