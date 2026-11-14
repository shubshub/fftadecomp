#include "ffta.h"

// Complete [0x0802BEB0, 0x0802C008): 344 bytes.
// f0b557464e464546e0b481b0099c09040f0c1204120c91461b041b0c9a462406240e0094
// 0e490e680e497418051c402252199046002f1dd10b4c2268402116f1adf90a480a4ab118
// 03684046202216f1a7f9281c60302268202116f19ff958e040f400025c060000b8d43608
// bcd436081c0b0000381c642116f1c2fd0004c10a002909d0034861180368281c202216f1
// 87f907e0bcd436080e480268281c202116f17cf9381c0a2116f1aafd0004000c0a2116f1
// e1fd0004c10a632f01d800290cd0054a281c203061181368202216f167f90ae0b8d43608
// bcd436081b49281c20300a68202116f159f9381c0a2116f1c3fd0004c10a164861180368
// 4046202216f14ef91149404620300a68202116f145f9fff721fd0f4c49460a19291c1023
// d4f784fdfff718fd51460a1910230099002900d008234146d4f778fd01b038bc9846a146
// aa46f0bc01bc0047b8d43608bcd4360800390106

typedef struct TransferRecord TransferRecord;
typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 *data_0200F440;
extern BufferInitializer g_callbacks_0836D4B8[];
extern BufferCopier data_0836D4BC[];
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

void func_0802BEB0(void *destination, u16 value, u16 first_offset,
                   u16 second_offset, u8 half)
{
    u8 *state = data_0200F440;
    u8 *digits = state + 0x65C;
    u8 *buffer = destination;
    u8 *second = buffer + 0x40;
    u32 tile;

    if (value == 0) {
        g_callbacks_0836D4B8[0](buffer, 0x40);
        data_0836D4BC[0](second, state + 0xB1C, 0x20);
        g_callbacks_0836D4B8[0](second + 0x20, 0x20);
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
        data_0836D4BC[0](second, digits + tile, 0x20);
        g_callbacks_0836D4B8[0](second + 0x20, 0x20);
    }

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06013900 + first_offset,
                  0x10);
    func_08000ADC(func_0802BA08(), second, (u8 *)0x06013900 + second_offset,
                  half ? 8 : 0x10);
}
