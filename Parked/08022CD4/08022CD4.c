#include "ffta.h"

typedef struct {
    u8 unknown_00[0x4A];
    u16 field_4a : 8;
    u16 field_4b : 8;
    u8 unknown_4c[2];
    u16 field_4e : 8;
} ControlState;

extern ControlState g_control_flags_03000940;
extern u8 data_0200F3D4[];

extern void func_0800363C(void);
extern void func_08007620(void *state, s16 first, s16 second, s16 third,
                          s16 duration);

/* Complete [0x08022CD4, 0x08022D48): 116 bytes. */
void func_08022CD4(u16 duration, u8 mode)
{
    switch (mode) {
    case 15:
        func_0800363C();
        func_08007620(data_0200F3D4, 16, 0, 0, (s16)duration);
        break;
    case 16: {
        ControlState *control = &g_control_flags_03000940;

        control->field_4a = 255;
        control->field_4b = 0;
        control->field_4e = 0;
        func_08007620(data_0200F3D4, 0, 0, 16, (s16)duration);
        break;
    }
    }
}
