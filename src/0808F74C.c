#include "ffta.h"

/* Complete [0x0808F74C, 0x0808F770): 36 bytes, 10 instructions. */
extern const u8 data_08A38ADC[];
extern const u8 data_08A3991C[];
extern u8 data_03005F28[];
extern void func_0814186C(const void *, void *, u32);

void func_0808F74C(void)
{
    u32 size = data_08A3991C - data_08A38ADC;
    func_0814186C(data_08A38ADC, data_03005F28, (size >> 1) & 0x1fffff);
}
