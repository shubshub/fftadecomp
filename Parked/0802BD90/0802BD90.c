#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 *data_0200F440;
extern BufferCopier data_0836D4BC[];
extern void func_0802BD44(void *destination, const void *source);
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x0802BD90, 0x0802BE40): 176 bytes.
 * f0b557464e464546e0b409040d0ca9461204120c92460c490c680c4909198846061c0b4f
 * 0b4aa1183b68202216f148fa002d13d1301c2030074aa1183b68202216f13efa23e00000
 * 40f400025c060000bcd43608dc0800001c0b0000281c0a2116f15efe0004c10a002903d0
 * 4144301cfff7a0ff48460a2116f18efe0004c10a301c203041443b68202216f119fafff7
 * f3fd064a5244311c1023d4f757fe38bc9846a146aa46f0bc01bc004700390106
 */
void func_0802BD90(void *destination, u16 value, u16 offset)
{
    u8 *state = data_0200F440;
    u8 *digits = state + 0x65C;
    u8 *buffer = destination;
    u32 tile;

    data_0836D4BC[0](buffer, state + 0x8DC, 0x20);
    if (value == 0) {
        data_0836D4BC[0](buffer + 0x20, state + 0xB1C, 0x20);
    } else {
        tile = (u16)(value / 10u) * 0x20;
        if (tile != 0)
            func_0802BD44(buffer, digits + tile);
        tile = (u16)(value % 10u) * 0x20;
        data_0836D4BC[0](buffer + 0x20, digits + tile, 0x20);
    }

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06013900 + offset, 0x10);
}
