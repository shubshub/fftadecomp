#include "ffta.h"

typedef void (*Callback08023F00)(u8 index, u8 *state);

extern u8 data_03002710[];
extern Callback08023F00 data_03002820[];
extern u8 data_03000E40[];
extern u8 g_state_0200F390;
extern u8 data_0600E000[];
extern u8 data_06005000[];
extern void func_080227E8(void);
extern void func_08006A7C(void *runner, Callback08023F00 *callbacks, u8 *states, u8 count);
extern void func_080231D8(u8 index, u8 *state);
extern void func_08121908(u8 index, u8 *state);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0808F74C(void);
extern void func_08023FD0(void);
extern void func_0802304C(void);
extern void func_080069F4(void *runner, u8 value);
extern u8 func_080241B4(void);
extern u8 func_08024108(void);

// Complete target [0x08023F00, 0x08023FCE), 206 bytes.
void func_08023F00(u8 unused, u8 *phase)
{
    u16 zero;
    u16 zero2;
    u32 value;
    u8 *state;

    switch (*phase) {
    case 0:
        func_08023FD0();
        *phase = 1;
        break;
    case 1:
        func_080227E8();
        func_08006A7C(data_03002710, data_03002820, data_03000E40, 9);
        func_08006ADC((Table *)data_03002710, 0, (u32)func_080231D8);
        func_08006ADC((Table *)data_03002710, 1, (u32)func_08121908);
        state = &g_state_0200F390;
        value = 0;
        *state = 9;
        zero = value;
        func_0814186C(&zero, data_0600E000, 0x01000800);
        zero2 = value;
        func_0814186C(&zero2, data_06005000, 0x01000800);
        func_0808F74C();
        *phase = 2;
        break;
    case 2:
        func_0802304C();
        func_080069F4(data_03002710, 9);
        *phase = func_080241B4();
        break;
    case 0xFF:
        break;
    case 0xFE:
        if (func_08024108())
            *phase = 0xFF;
        break;
    }
}
