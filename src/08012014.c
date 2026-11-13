#include "ffta.h"

typedef struct Transfer08012014 {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct Transfer08012014 *next;
} Transfer08012014;

typedef struct {
    u8 unknown_00[0x2c];
    union {
        void *unit;
        u32 packed;
    } subject;
    u32 tile_offset;
    u8 unknown_34[6];
    u16 options;
    u8 unknown_3c[0x758 - 0x3c];
    Transfer08012014 first_transfer;
    Transfer08012014 second_transfer;
} Context08012014;

typedef void (*BufferCopier08012014)(void *destination, const void *source,
                                    u32 size);

extern Context08012014 *data_0200918C;
extern u8 data_02003CB0[];
extern u8 data_03003B20[];
extern u8 data_06010000[];
extern BufferCopier08012014 const data_0836D4BC[];
extern u8 func_080CB78C(void *unit);
extern u8 func_080C8240(void *unit);
extern u8 func_080CB7C0(void *unit, u8 selector);
extern u32 func_080CB8B4(void *destination, u8 index);
extern void func_08000ADC(Transfer08012014 *record, const void *source,
                          void *destination, u16 words);
extern void func_080CB8D4(void *object, u8 index);

/* Target: complete [0x08012014, 0x080120F0), 220 bytes.
 * f0b557464e464546e0b407480268518f80200840002809d1d16a080a0006050e0906
 * 0f0e15e000008c910002d46a201cb9f0a2fb0006050e201cb6f0f7f8002100060028
 * 00d10121201cb9f0affb0006070e1c4e301c291cb9f022fc041c2404200c8046640c
 * 2404250c17498a460968eb22d20088180a6b144989464a44a40c311c231ceef720fd
 * 5046026810495018a9194d44126b5219231ceef715fdb0444046391cb9f00cfc0a49
 * 0b480b684146602230f1c3f838bc9846a146aa46f0bc01bc0047b03c00028c910002
 * 0000010674070000bcd43608203b0003
 */
void func_08012014(void)
{
    u8 graphic;
    u8 palette;
    u16 size;
    u16 half;

    if (!(data_0200918C->options & 0x80)) {
        graphic = data_0200918C->subject.packed >> 8;
        palette = data_0200918C->subject.packed;
    } else {
        void *unit = data_0200918C->subject.unit;

        graphic = func_080CB78C(unit);
        palette = func_080CB7C0(unit, !func_080C8240(unit));
    }
    size = func_080CB8B4(data_02003CB0, graphic);
    half = size >> 1;
    func_08000ADC(&data_0200918C->first_transfer, data_02003CB0,
                  data_06010000 + data_0200918C->tile_offset, half >> 2);
    func_08000ADC(&data_0200918C->second_transfer, data_02003CB0 + half,
                  data_06010000 + data_0200918C->tile_offset + half,
                  half >> 2);
    func_080CB8D4(data_02003CB0 + size, palette);
    data_0836D4BC[0](data_03003B20, data_02003CB0 + size, 0x60);
}
