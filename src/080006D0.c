/* Target: 0x080006D0, 72 bytes. Saves display control and restores interrupt control. */
typedef unsigned short u16;
struct InterruptState {
    u16 unknown_00;
    u16 unknown_02;
    u16 unknown_04;
    u16 interrupt_enable;
};

void func_080006D0(void)
{
    *(u16 *)0x03002BBC = *(u16 *)0x04000000;
    *(u16 *)0x04000000 = 0x80;
    *(u16 *)0x03000E50 = ((struct InterruptState *)0x03000EA0)->interrupt_enable & 0xFFF8;
    *(u16 *)0x04000200 = *(u16 *)0x03000E50;
}
