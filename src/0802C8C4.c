#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    u8 unknown_00[0x0C];
    const void *field_0C;
    u16 flags;
    u8 unknown_12[3];
    u8 field_15;
    s16 field_16;
    u8 unknown_18[0x10];
    u8 tiles[0x100];
    u8 tiles_128[0x20];
    u8 tiles_148[0x80];
    u8 tiles_1C8[0x60];
    u8 tiles_228[0x80];
    u8 tiles_2A8[0x20];
} Object0802C8C4;

extern u8 *data_0200F440;
extern BufferCopier data_0836D4BC[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0802C830(void *destination, s16 value);
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern void func_08015110(void *, void *, const void *, u32, u32);
extern void func_0802BAF8(void *destination, const void *source);
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

// Complete [0x0802C8C4, 0x0802C9F4): 304 bytes.
// f0b582b0061c318a022008400004040c002c57d0341c283401a900200880224a081c211c
// 14f1c0ff204f214d296821480918802252003b68201c15f1a7fc1621705e002809da9422
// 5200b01829681a4a89183b68202215f199fca421490070181622b15e002900da49420904
// 0914fff77dffe42149007018717dfff777ff8a229200b01829680d4a89183b68402215f1
// 7dfcaa21890070182968094a89183b68202215f173fc32e080010001bcd4360840f40002
// fc0800003c0a00005c0f00001c0a0000c0208000f5f758ff051c684606300480134a291c
// 14f166fff06800219bf07efa021c10480068f3218900401801210091291c0023e8f7a8fb
// 341c2834201c291cfff796f8281cf5f741fffff719f8064a211cc023d4f77ef802b0f0bc
// 01bc00478001000140f40002c0970006
void func_0802C8C4(Object0802C8C4 *object)
{
    if (object->flags & 2) {
        u8 *tiles = object->tiles;
        u16 fill;
        u16 *fill_source = &fill;

        *fill_source = 0;
        func_0814186C(fill_source, tiles, 0x01000180);
        data_0836D4BC[0](object->tiles, data_0200F440 + 0x8FC, 0x100);
        if (object->field_16 < 0)
            data_0836D4BC[0](object->tiles_128, data_0200F440 + 0xA3C, 0x20);
        func_0802C830(object->tiles_148,
                      object->field_16 < 0 ? -object->field_16 : object->field_16);
        func_0802C830(object->tiles_1C8, object->field_15);
        data_0836D4BC[0](object->tiles_228, data_0200F440 + 0xF5C, 0x40);
        data_0836D4BC[0](object->tiles_2A8, data_0200F440 + 0xA1C, 0x20);
    } else {
        u8 *buffer = func_08022840(0x300);
        u16 clear = 0;

        func_0814186C(&clear, buffer, 0x01000180);
        func_08015110(data_0200F440 + 0x3CC, buffer,
                      (const void *)func_080C7EA4(object->field_0C, 0), 0, 1);
        func_0802BAF8(object->tiles, buffer);
        func_08022854(buffer);
    }
    func_08000ADC(func_0802BA08(), object->tiles, (void *)0x060097C0, 0xC0);
}
