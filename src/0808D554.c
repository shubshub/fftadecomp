#include "ffta.h"

typedef struct {
    u8 unknown_000[0xc1d];
    u8 field_c1d;
    u8 unknown_c1e[0x3e];
    u16 entries[6];
} State0808D554;

extern State0808D554 *data_03002818;
extern void func_08141540(u32 sound);

/* Complete target [0x0808D554, 0x0808D5BC): 104 bytes, 42 instructions.
 * f0b508480168084a89180e78051c2b1c0024186881180878042807d80130087005e00000182800031d0c00000c7019688818007840000a4fc919091808880028e7d02868074c00190078864202d06520b3f0ccff286800190078f0bc02bc08475c0c00001d0c0000
 */
u8 func_0808D554(void)
{
    u8 previous = data_03002818->field_c1d;

    do {
        if (data_03002818->field_c1d <= 4)
            data_03002818->field_c1d++;
        else
            data_03002818->field_c1d = 0;
    } while (data_03002818->entries[data_03002818->field_c1d] == 0);

    if (previous != data_03002818->field_c1d)
        func_08141540(0x65);

    return data_03002818->field_c1d;
}
