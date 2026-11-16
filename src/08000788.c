/* Target: 0x08000788-0x080007C8, 64 bytes including the literal pool:
 * 80b56f4609480a490a89028009480849ca880280084807490a8802808020c00406490a88
 * 028080bc01bc004704000004a00e0003500e000300020004bc2b0003
 * Undoes func_080006D0 (src/080006D0.c): writes display status and the
 * unmasked interrupt enable from 0x03000EA0, and restores display control
 * from the copy func_080006D0 saved at 0x03002BBC.
 * Built at -O0, like its caller at 0x080004B0 and func_080006D0: the r7 frame
 * (push {r7, lr}; mov r7, sp) and the pool reloads of 0x03000EA0 at
 * 0x08000796 and of 0x03000E50 at 0x0800079E are -O0 code; at -O2 this
 * source compiles to 52 bytes. */
typedef unsigned short u16;
struct InterruptState {
    u16 unknown_00;
    u16 unknown_02;
    u16 unknown_04;
    u16 interrupt_enable;
    u16 display_status;
};

extern struct InterruptState data_03000EA0;
extern u16 data_03000E50;
extern u16 data_03002BBC;
extern u16 data_04000004;
extern u16 data_04000200;

void func_08000788(void)
{
    data_04000004 = data_03000EA0.display_status;
    data_03000E50 = data_03000EA0.interrupt_enable;
    data_04000200 = data_03000E50;
    /* DISPCNT: the ROM builds 0x04000000 with movs/lsls at 0x080007A4 rather
     * than loading it from the pool. */
    *(u16 *)0x04000000 = data_03002BBC;
}
