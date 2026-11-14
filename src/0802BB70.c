#include "ffta.h"

// Complete [0x0802BB70, 0x0802BC7C): 268 bytes.
// f0b5474680b409040e0c1204120c90460b490d680b496f18041c002e1ad10a480268201c
// 402116f159fb084a201c4030074be9181368202216f152fb53e0000040f400025c060000
// b8d43608bcd436081c0b0000301c642116f172ff0004c10a002909d0034879180368201c
// 202216f137fb07e0bcd436080e480268201c202116f12cfb301c0a2116f15aff0004000c
// 0a2116f191ff0004c10a632e01d800290cd0054a201c203079181368202216f117fb0ae0
// b8d43608bcd436081049201c20300a68202116f109fb301c0a2116f173ff0004c10a0b4a
// 201c403079181368202216f1fdfafff7d7fe074a4244211c1823d4f73bff08bc9846f0bc
// 01bc0047b8d43608bcd4360800390106

typedef struct TransferRecord TransferRecord;
typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 *data_0200F440;
extern BufferInitializer g_callbacks_0836D4B8[];
extern BufferCopier data_0836D4BC[];
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

void func_0802BB70(void *destination, u16 value, u16 offset)
{
    u8 *state = data_0200F440;
    u8 *digits = state + 0x65C;
    u8 *buffer = destination;
    u32 tile;

    if (value == 0) {
        g_callbacks_0836D4B8[0](buffer, 0x40);
        data_0836D4BC[0](buffer + 0x40, state + 0xB1C, 0x20);
    } else {
        tile = value / 100 * 0x20;
        if (tile != 0)
            data_0836D4BC[0](buffer, digits + tile, 0x20);
        else
            g_callbacks_0836D4B8[0](buffer, 0x20);
        tile = value / 10 % 10 * 0x20;
        if (value > 99 || tile != 0)
            data_0836D4BC[0](buffer + 0x20, digits + tile, 0x20);
        else
            g_callbacks_0836D4B8[0](buffer + 0x20, 0x20);
        tile = value % 10 * 0x20;
        data_0836D4BC[0](buffer + 0x40, digits + tile, 0x20);
    }

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06013900 + offset, 0x18);
}
