#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferInitializer)(void *destination, u32 size);
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 *data_0200F440;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern BufferCopier const data_0836D4BC[];
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x0802BC7C, 0x0802BD44): 200 bytes.
 * f0b5474680b409040c0c1204120c90460b490e680b497718051c002c1ad10a480268281c
 * 202116f1d3fa084a281c2030074bf1181368202216f1ccfa30e0000040f400025c060000
 * b8d43608bcd436081c0b0000201c0a2116f1ecfe0004c10a002909d0034879180368281c
 * 202216f1b1fa07e0bcd4360810480268281c202116f1a6fa201c0a2116f110ff0004c10a
 * 0b4a281c203079181368202216f19afafff774fe074a4244291c1023d4f7d8fe08bc9846
 * f0bc01bc00470000b8d43608bcd4360800390106
 */
void func_0802BC7C(void *destination, u16 value, u16 offset)
{
    u8 *state = data_0200F440;
    u8 *digits = state + 0x65C;
    u8 *buffer = destination;
    u32 tile;

    if (value == 0) {
        g_callbacks_0836D4B8[0](buffer, 0x20);
        data_0836D4BC[0](buffer + 0x20, state + 0xB1C, 0x20);
    } else {
        tile = (u16)(value / 10u) * 0x20;
        if (tile != 0)
            data_0836D4BC[0](buffer, digits + tile, 0x20);
        else
            g_callbacks_0836D4B8[0](buffer, 0x20);
        tile = (u16)(value % 10u) * 0x20;
        data_0836D4BC[0](buffer + 0x20, digits + tile, 0x20);
    }

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06013900 + offset, 0x10);
}
