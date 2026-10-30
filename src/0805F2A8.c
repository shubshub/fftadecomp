#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 phase;
    u8 unknown_119A[3];
    u8 selection;
    u8 unknown_119E[4];
    u8 event;
} State0805F2A8;

extern State0805F2A8 *data_0200F448;
extern u8 func_0805D174(void);
extern void func_08013364(void);
extern void func_080610F8(u8 value);
extern u16 func_08011860(void);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);

/* Target [0x0805F2A8, 0x0805F330), 136 complete bytes:
 * f0b5054e3568054fe8190078002807d001281dd034e0000048f4000299110000
 * fdf754ff00065221002800d05321074c28190170b4f742f830680019007801f007ff
 * 3068c0190121017019e09d110000b2f7b2fa0004002812d00020002100220023
 * caf7d9ff306804494018a72101703068c019ff210170012002e0a21100000020
 * f0bc02bc0847
 */
u8 func_0805F2A8(void)
{
    State0805F2A8 *state = data_0200F448;

    switch (state->phase) {
    case 0:
        state->selection = func_0805D174() ? 0x53 : 0x52;
        func_08013364();
        func_080610F8(data_0200F448->selection);
        data_0200F448->phase = 1;
        break;
    case 1:
        if (func_08011860()) {
            func_0802A2C0(0, 0, 0, 0);
            data_0200F448->event = 0xA7;
            data_0200F448->phase = 0xFF;
            return 1;
        }
        break;
    }
    return 0;
}
