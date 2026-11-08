#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);
typedef void (*BufferInitializer)(void *destination, u32 size);

extern u8 *data_0200F440;
extern BufferCopier data_0836D4BC[];
extern BufferInitializer g_callbacks_0836D4B8[];
extern void func_0802BD44(void *destination, const void *source);
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x0802C72C, 0x0802C7E0): 180 bytes.
 * f0b557464e464546e0b4071c0904090c8a46120621480068214944189026f600002a00d0
 * 403e1f4989461f490918884648460368381c202215f174fd1b4d381c20302a68202115f1
 * 6bfd381c1030a419211cfff7e1fa381c403049460b684146202215f15ffd381c60302a68
 * 202115f157fd381c50302034211cfff7cdfafff72df90b4a5244391c2023d4f791f938bc
 * 9846a146aa46f0bc01bc004740f400025c060000bcd436087c0a0000b8d4360840940006
 */
void func_0802C72C(u8 *buffer, u16 offset, u8 alternate)
{
    u8 *state = data_0200F440;
    u8 *source = state + 0x65C;
    s32 select = 0x480;

    if (alternate)
        select -= 0x40;

    data_0836D4BC[0](buffer, state + 0xA7C, 0x20);
    g_callbacks_0836D4B8[0](buffer + 0x20, 0x20);
    func_0802BD44(buffer + 0x10, source + select);

    data_0836D4BC[0](buffer + 0x40, state + 0xA7C, 0x20);
    g_callbacks_0836D4B8[0](buffer + 0x60, 0x20);
    func_0802BD44(buffer + 0x50, source + select + 0x20);

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06009440 + offset, 0x20);
}
