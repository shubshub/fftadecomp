typedef unsigned char u8;

extern u8 g_state_02000000[];
extern void func_080C9574(int flag, u8 enabled);

/* Target: 080CBBC4..080CBC14, 80 bytes. */
void func_080CBBC4(void)
{
    int value = g_state_02000000[0x21B4];

    if (value == 10 || value == 20 || value == 30 || value == 40 ||
        value == 50 || value == 60 || value == 70 || value == 80 || value == 90) {
        func_080C9574(60, 1);
    } else if (value == 96) {
        func_080C9574(60, 1);
    }
}
