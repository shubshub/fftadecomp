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

// Complete [0x0802C624, 0x0802C72C): 264 bytes.
// f0b557464e464546e0b481b0041c09040e0c1204120c009218480568184840198246632e
// 00d9632616498846164aaf180b68201c391c202215f1f8fd134b9946201c20301a682021
// 15f1eefd002e21d1201c403041460b68391c202215f1e6fd201c60304b461a68202115f1
// ddfd201c5030074aa918fff753fb32e040f400025c060000bcd436087c0a0000b8d43608
// 3c0b0000301c0a2116f1f8f94005010c002904d0201c10305144fff739fb201c40304146
// 0b68391c202215f1b7fd201c60304b461a68202115f1aefd301c0a2116f118fa4005010c
// 201c50305144fff71ffbfff77ff90099064bca18211c2023d4f7e2f901b038bc9846a146
// aa46f0bc01bc004740940006
void func_0802C624(u8 *buffer, u16 value, u16 offset)
{
    u8 *state = data_0200F440;
    u8 *digits = state + 0x65C;
    u16 glyph;

    if (value > 99)
        value = 99;

    data_0836D4BC[0](buffer, state + 0xA7C, 0x20);
    g_callbacks_0836D4B8[0](buffer + 0x20, 0x20);

    if (value == 0) {
        data_0836D4BC[0](buffer + 0x40, state + 0xA7C, 0x20);
        g_callbacks_0836D4B8[0](buffer + 0x60, 0x20);
        func_0802BD44(buffer + 0x50, digits + 39 * 0x20);
    } else {
        glyph = value / 10 * 0x20;
        if (glyph != 0)
            func_0802BD44(buffer + 0x10, digits + glyph);

        data_0836D4BC[0](buffer + 0x40, state + 0xA7C, 0x20);
        g_callbacks_0836D4B8[0](buffer + 0x60, 0x20);
        glyph = value % 10 * 0x20;
        func_0802BD44(buffer + 0x50, digits + glyph);
    }

    func_08000ADC(func_0802BA08(), buffer, (u8 *)0x06009440 + offset, 0x20);
}
