#include "ffta.h"

typedef struct {
    u16 unknown_00[3];
    u16 interrupt_enable;
    u16 display_status;
} InterruptState;

extern InterruptState data_03000EA0;
extern u16 data_03000E50;
/* IE, IME and DISPSTAT are halfword I/O registers. */
extern u16 data_04000200;
extern u16 data_04000208;
extern u16 data_04000004;
extern u32 data_0200F370;
extern void (*data_030008E8)(void);

extern void func_08004AC0(void);
extern u16 func_08141984(u8 timer, void (**handler)(void));
extern void func_0813AE30(void);

void func_080005CC(void)
{
    func_08004AC0();
    data_03000EA0.interrupt_enable |= 0x2003;
    data_03000E50 = data_03000EA0.interrupt_enable;
    data_04000200 = data_03000E50;
    data_04000208 = 1;
    data_03000EA0.display_status = 8;
    data_04000004 = data_03000EA0.display_status;

    if (data_0200F370 != 0) {
        if (func_08141984(2, &data_030008E8) != 0)
            data_0200F370 = 0;
        else
            func_0813AE30();
    }
}
