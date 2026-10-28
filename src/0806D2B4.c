#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1a88];
    u8 context[0x29e4];
    u8 saved_state;
} State0806D2B4;

extern State0806D2B4 *data_0200F428;
extern u8 func_0806FE14(void *);
extern void func_08141540(u16);

/* Complete [0x0806D2B4, 0x0806D300): 76 bytes, 28 instructions. */
void func_0806D2B4(u8 *state)
{
    if (func_0806FE14(data_0200F428->context) == 1) {
        data_0200F428->saved_state = *state;
        *state = 62;
        func_08141540(104);
    } else {
        *state = 80;
        func_08141540(105);
    }
}
