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
extern const u8 *func_08141BB0(const u8 *source, const u8 *flash, u32 size);

typedef const u8 *(*FlashVerify)(const u8 *source, const u8 *flash, u32 size);

/* FLASH512_V130 full-sector verification, 0x08141BE0..0x08141C78. */
u32 func_08141BE0(u16 sector, void *source)
{
    u16 readBuffer[128];
    u16 *readCode;
    u16 *dest;
    u16 count;
    FlashVerify verify;

    data_04000204 = (data_04000204 & ~3) | 3;
    if (data_0200F370->romSize == 0x20000) {
        func_0814189C(sector >> 4);
        sector &= 15;
    }
    readCode = (u16 *)func_08141BB0;
    readCode = (u16 *)((u32)readCode ^ 1);
    dest = readBuffer;
    count = ((s32)func_08141BE0 - (s32)func_08141BB0) >> 1;
    while (count != 0) {
        *dest++ = *readCode++;
        count--;
    }
    verify = (FlashVerify)((u32)readBuffer + 1);
    return (u32)verify(source, (u8 *)(0x0E000000 + (sector << data_0200F370->sector.shift)),
                       (u16)data_0200F370->sector.size);
}
