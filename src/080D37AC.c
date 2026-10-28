typedef unsigned char u8;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D37AC..0x080D37C4: 24 bytes. */
void func_080D37AC(void)
{
    u8 *state = func_08005BFC(data_020159C0);

    *state = 0;
}
