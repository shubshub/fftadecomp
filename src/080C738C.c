#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAE];
    u8 flags;
} State080C738C;

extern State080C738C data_02015738;
extern void func_08004CD4(void);

/* Complete [0x080C738C, 0x080C73B0): 36 bytes, 15 instructions. */
void func_080C738C(void)
{
    if (!(data_02015738.flags & 0x80)) {
        data_02015738.flags |= 0xC0;
        func_08004CD4();
    }
}
