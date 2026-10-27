#include "ffta.h"

extern void func_0805F3C4(u32 size);
extern void func_0805F414(void);

/* 0805D0E0..0805D108: 40 bytes. */
void func_0805D0E0(void *task, u8 *state)
{
    switch (*state) {
    case 0:
        func_0805F3C4(0x3000);
        *state = 1;
        break;
    case 0xFF:
        func_0805F414();
        break;
    }
}
