#include "ffta.h"

/* Complete [0x08141D9C, 0x08141E30): 148 bytes, 53 instructions and nine
 * literal-pool words.  agb_flash FLASH512_V130 (config/library_units.json):
 * sets the SRAM wait state, reads the flash ID, scans the setup table at
 * 0x0836CE38 up to the entry with a zero maker ID, and installs the matched
 * (or terminating) entry's routines and FlashType.  Returns 0 when the ID
 * was found and 1 otherwise, as a u16: the -O0 caller zero-extends it
 * (lsls/lsrs #16 at 0x0800034A). */

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

struct FlashSetupInfo {
    u16 (*programFlashSector)(u16 sector, void *source);
    u16 (*eraseFlashChip)(void);
    u16 (*eraseFlashSector)(u16 sector);
    u16 (*waitForFlashWrite)(u8 phase, u8 *address, u8 lastData);
    const u16 *maxTime;
    struct FlashType type;
};

extern const struct FlashSetupInfo *const data_0836CE38[];
extern u16 (*data_0200F36C)(u16 sector, void *source);
extern u16 (*data_0200F378)(void);
extern u16 (*data_0200F37C)(u16 sector);
extern u16 (*data_0200F368)(u8 phase, u8 *address, u8 lastData);
extern const u16 *data_0200F380;
extern const struct FlashType *data_0200F370;
extern u16 func_081418C0(void);

u16 func_08141D9C(void)
{
    u16 result;
    u16 flashId;
    const struct FlashSetupInfo *const *setupInfo;

    *(u16 *)0x04000204 = (*(u16 *)0x04000204 & ~3) | 3;

    flashId = func_081418C0();

    setupInfo = data_0836CE38;
    result = 1;

    for (;;) {
        if ((*setupInfo)->type.ids.separate.makerId == 0)
            break;
        if (flashId == (*setupInfo)->type.ids.joined) {
            result = 0;
            break;
        }
        setupInfo++;
    }

    data_0200F36C = (*setupInfo)->programFlashSector;
    data_0200F378 = (*setupInfo)->eraseFlashChip;
    data_0200F37C = (*setupInfo)->eraseFlashSector;
    data_0200F368 = (*setupInfo)->waitForFlashWrite;
    data_0200F380 = (*setupInfo)->maxTime;
    data_0200F370 = &(*setupInfo)->type;

    return result;
}
