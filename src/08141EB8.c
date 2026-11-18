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

/* FLASH512_V130 chip erase. The phase-3 wait reads the first byte of flash
 * through the Thumb reader installed in this local buffer. */
u16 func_08141EB8(void)
{
    u16 readBuffer[32];
    u16 result;

    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | data_0200F370->wait[0];
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0x80;
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0x10;
    func_08141AB0(readBuffer);
    result = data_0200F368(3, (u8 *)0x0E000000, 0xFF);
    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | 3;

    return result;
}
