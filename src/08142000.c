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

extern u32 func_08142124(const u8 *bytes);
extern u32 func_08142148(const u8 *bytes, u32 (*scan)(const u8 *));

/* FLASH512_V130 sector programmer installed for D4BF and the fallback setup. */
u16 func_08142000(u16 sector, void *source)
{
    u16 readBuffer[48];
    u8 *destination;
    u16 *scanSource;
    u16 *scanDestination;
    u16 count;
    u8 tries;
    u8 extra;
    u16 result;

    if (sector >= 16)
        return 0x80FF;
    destination = (u8 *)(0x0E000000 + (sector << data_0200F370->sector.shift));
    scanSource = (u16 *)((u32)func_08142124 ^ 1);
    scanDestination = readBuffer;
    count = (u32)func_08142148 - (u32)func_08142124;
    while (count != 0) {
        *scanDestination++ = *scanSource++;
        count -= 2;
    }

    tries = 0;
    for (;;) {
        result = func_08141F2C(sector);
        if (result == 0) {
            result = func_08142148(destination, (u32 (*)(const u8 *))((u32)readBuffer + 1));
            if (result == 0)
                break;
        }
        if (++tries == 81)
            return result;
    }
    extra = 1;
    if (tries != 0)
        extra = 6;
    for (tries = 1; tries <= extra; tries++)
        func_08141F2C(sector);

    func_08141AB0(readBuffer);
    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | data_0200F370->wait[0];
    data_0200F374 = data_0200F370->sector.size;
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
