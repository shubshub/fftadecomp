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
extern u16 (*data_0200F368)(u8 phase, u8 *address, u8 lastData);
extern void func_08141AB0(u16 *target);

/* FLASH512_V130 sector erase. The stack buffer holds the RAM copy of the
 * byte reader while the phase-2 wait polls the first byte of the sector. */
u16 func_08141F2C(u16 sector)
{
    u16 readBuffer[32];
    u8 *address;
    u16 result;

    if (sector >= 16)
        return 0x80FF;

    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | data_0200F370->wait[0];
    address = (u8 *)(0x0E000000 + (sector << data_0200F370->sector.shift));
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0x80;
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *address = 0x30;
    func_08141AB0(readBuffer);
    result = data_0200F368(2, address, 0xFF);
    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | 3;

    return result;
}
