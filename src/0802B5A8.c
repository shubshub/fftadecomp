#include "ffta.h"

/* Complete [0x0802B5A8, 0x0802B630): 136 bytes.
 * f0b581b0061c0f4f0f4b002e24d08024e400a508391c1a1c2b1cd5f78bfa301c1c303919
 * 084aa418221c2b1cd5f782fa064b07480090074a6846191c16f142f918e00000f4d93b08
 * 0039010600410106666666660001000580229200381c191c16f12ef9054b06480090064a
 * 6846191c16f128f901b0f0bc01bc0047004101066666666600010005
 */

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

extern const u8 data_083BD9F4[];
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0802B5A8(TransferRecord *records)
{
    const u8 *source = data_083BD9F4;
    /* OBJ VRAM as a plain number: the pool word 0x06013900 (0x0802B5F0) has
     * no relocation, and data_06013900 changes the code (144 bytes).  The
     * fill area, 0x06014100 in the pool at 0x0802B5F4 and 0x0802B624, starts
     * right after the 0x800 bytes of data_083BD9F4 copied there. */
    u8 *vram = (u8 *)0x06013900;
    u32 size;
    u32 fill;

    if (records != 0) {
        size = 0x400;
        func_08000ADC(records, source, vram, size / 4);
        func_08000ADC(records + 1, source + size, vram + size, size / 4);
        vram += 0x800;
        fill = 0x66666666;
        func_0814186C(&fill, vram, 0x05000100);
    } else {
        func_08141868(source, vram, 0x200);
        vram += 0x800;
        fill = 0x66666666;
        func_0814186C(&fill, vram, 0x05000100);
    }
}
