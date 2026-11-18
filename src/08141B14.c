#include "ffta.h"

struct FlashSector {
    u32 size;
    u8 shift;
    u16 count;
    u16 top;
};

struct FlashType {
    u32 romSize;
    struct FlashSector sector;
    u16 wait[2];
    union {
        struct {
            u8 makerId;
            u8 deviceId;
        } separate;
        u16 joined;
    } ids;
};

extern const struct FlashType *data_0200F370;
extern u16 data_04000204;
extern void func_0814189C(u8 bank);
extern void func_08141AF0(const u8 *source, u8 *destination, u32 size);

typedef void (*FlashRead)(const u8 *source, u8 *destination, u32 size);

/* FLASH512_V130 ReadFlash, 0x08141B14..0x08141BB0. */
void func_08141B14(u16 sector, u32 offset, u8 *destination, u32 size)
{
    u16 readBuffer[64];
    u16 *readCode;
    u16 *dest;
    u16 count;
    FlashRead read;


    data_04000204 = (data_04000204 & ~3) | 3;
    if (data_0200F370->romSize == 0x20000) {
        func_0814189C(sector >> 4);
        sector &= 15;
    }
    readCode = (u16 *)func_08141AF0;
    readCode = (u16 *)((u32)readCode ^ 1);
    dest = readBuffer;
    count = ((s32)func_08141B14 - (s32)func_08141AF0) >> 1;
    while (count != 0) {
        *dest++ = *readCode++;
        count--;
    }
    read = (FlashRead)((u32)readBuffer + 1);
    read((const u8 *)(0x0E000000 + (sector << data_0200F370->sector.shift) + offset), destination, size);
}
