#include "ffta.h"

// Complete target [0x08031348, 0x080314C8): 384 bytes, 131 instructions
// and 20 literal words.

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 width;
    u8 height;
    u8 *tiles;
    void *destination;
} Display08031348;

extern Display08031348 data_03000E60;
extern Display08031348 data_03000E80;
extern Display08031348 data_030008B0;
extern Display08031348 data_03000990;
extern u8 data_02003CB0[];
extern u8 data_03003860[];
extern u8 data_06008000[];
extern u8 data_06008A40[];
extern u8 data_06010000[];
extern u8 data_06010100[];
extern u8 data_060134C0[];
extern u8 data_06010E40[];
extern const u8 data_083A94CC[];
extern const u8 data_083A93AC[];
extern const u8 data_083AD5F8[];
extern const u8 data_083ADB08[];
extern const u8 data_083AA184[];
extern const u8 data_083AE194[];

extern void func_08005318(const void *source, void *destination, u32 index,
                          u32 flag);
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080314C8(u32 update);

void func_08031348(void)
{
    u8 *buffer = data_02003CB0;
    u16 fill0;
    u16 fill1;
    u16 fill2;
    u16 fill3;
    u16 fill4;
    u16 *source0;
    u16 *source1;
    u16 *source2;
    u16 *source3;
    u16 *source4;
    u32 zero0;
    u32 zero1;

    source0 = &fill0;
    *source0 = 0;
    func_0814186C(source0, data_03000E60.destination,
                  0x01000000 | (data_03000E60.width * data_03000E60.height));
    source1 = &fill1;
    *source1 = 0;
    func_0814186C(source1, data_03000E80.destination,
                  0x01000000 | (data_03000E80.width * data_03000E80.height));
    source2 = &fill2;
    *source2 = 0;
    func_0814186C(source2, data_030008B0.destination,
                  0x01000000 | (data_030008B0.width * data_030008B0.height));
    source3 = &fill3;
    *source3 = 0;
    func_0814186C(source3, data_03000990.destination,
                  0x01000000 | (data_03000990.width * data_03000990.height));
    source4 = &fill4;
    *source4 = 0;
    func_0814186C(source4, data_03000E60.tiles, 0x01004000);

    func_08005318(data_083A94CC, buffer, 0, 0);
    func_08141868(buffer, data_06008000, 0x290);
    func_08005318(data_083A93AC, buffer, 0, 0);
    func_08141868(buffer, data_06010000, 0x40);
    func_0800543C(buffer, data_083AD5F8);
    func_08141868(buffer, data_06008A40, 0x318);
    func_0800543C(buffer, data_083ADB08);
    func_08141868(buffer, data_06010100, 0x220);
    func_08005318(data_083AA184, buffer, 0, 0);
    func_08141868(buffer, data_060134C0, 0x5A0);
    func_0800543C(buffer, data_083AE194);
    func_08141868(buffer, data_06010E40, 0x500);

    zero0 = 0;
    func_0814186C(&zero0, data_03003860, 0x05000080);
    zero1 = 0;
    func_0814186C(&zero1, data_03003860 + 0x200, 0x05000080);
    func_080314C8(0);
}
