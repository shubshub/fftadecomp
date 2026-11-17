#include "ffta.h"

/* Complete [0x08141E30, 0x08141EB8): 136 bytes, 55 instructions and four
 * literal-pool words.  agb_flash FLASH512_V130 (config/library_units.json):
 * WaitForFlashWrite512K_Common of SAT-R/sa2 src/lib/agb_flash/agb_flash_512k.c
 * (pret's WaitForFlashWrite_Common without the status & 0x20 test).  Starts
 * the flash timer for the phase, polls the status byte at the address
 * through the routine held at 0x0200F364 until it reads lastData, and on a
 * timeout (0x0200F360) re-polls once; if the chip is still busy it resets a
 * Macronix part (maker ID 0xC2) with 0xF0 at 0x0E005555 and returns
 * 0xC000 | phase.  Stops the timer and returns 0 on success. */

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

extern u8 data_0200F360;
extern u8 (*data_0200F364)(u8 *addr);
extern const struct FlashType *data_0200F370;
extern void func_081419C0(u8 phase);
extern void func_08141A68(void);

u16 func_08141E30(u8 phase, u8 *addr, u8 lastData)
{
    u16 result = 0;
    u8 status;

    func_081419C0(phase);

    while ((status = data_0200F364(addr)) != lastData) {
        if (data_0200F360) {
            if (data_0200F364(addr) == lastData)
                break;

            /* FLASH_WRITE(0x5555, 0xF0) in the reference, a vu8 store; the
             * volatile spelling gives the same 136 bytes. */
            if (data_0200F370->ids.separate.makerId == 0xC2)
                *(u8 *)0x0E005555 = 0xF0;

            result = phase | 0xC000u;
            break;
        }
    }

    func_08141A68();

    return result;
}
