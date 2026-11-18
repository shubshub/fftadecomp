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
extern u16 data_0200F374;
extern u16 func_08141F2C(u16 sector);
extern void func_08141AB0(u16 *target);
extern u16 func_08141FC8(u8 *source, u8 *destination);

/* FLASH512_V130 sector programmer installed for the 1B32 and 1CC2 chips. */
u16 func_08142160(u16 sector, void *source)
{
    u16 readBuffer[32];
    u8 *destination;
    u16 result;

    if (sector >= data_0200F370->sector.count)
        return 0x80FF;
    result = func_08141F2C(sector);
    if (result)
        return result;

    func_08141AB0(readBuffer);
    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | data_0200F370->wait[0];
    data_0200F374 = data_0200F370->sector.size;
    destination = (u8 *)(0x0E000000 + (sector << data_0200F370->sector.shift));
    while (data_0200F374) {
        result = func_08141FC8(source, destination);
        if (result)
            break;
        data_0200F374--;
        source = (u8 *)source + 1;
        destination++;
    }
    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | 3;
    return result;
}
