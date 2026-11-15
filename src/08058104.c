#include "ffta.h"

/* Complete target: [0x08058104, 0x080581AA), 166 bytes, 74 instructions,
 * including the one literal word (data_02003CB0).
 *
 * Scrolls a three-row window by one row through the scratch buffer
 * data_02003CB0.  A row is width * 5 tiles (func_08057E98 draws row `row`
 * at tile row * 5 * width) and each copy moves two rows.  Direction 0x80
 * copies rows 1-2 to rows 0-1, direction 0x40 copies rows 0-1 to rows 1-2,
 * and either way row `row` is redrawn with func_08057E98.  Each control
 * word is the copy's byte size converted to a halfword count, the CpuCopy16
 * shape of src/0802B07C.c and src/0800DA88.c; `width` is a byte, so the
 * mask folds away.
 *
 * Target bytes:
 *   f0b557464e464546e0b483b0051c0b980906090e8a4600911206120e9146494601911b06
 *   1b0e9846414602910004020c0d4f697d88004418261c802a16d16100e86840180c1c391c
 *   221ce9f08dfbe968381c221ce9f088fb281c414652464b46fff798fe17e00000b03c0002
 *   402a12d1e8687400391c221ce9f076fb201ce9680918381c221ce9f06ffb281c0299009a
 *   019bfff77ffe03b038bc9846a146aa46f0bc01bc0047
 */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
} MenuWindow;

extern u16 data_02003CB0[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08057E98(MenuWindow *window, u8 row, u8 unitId, u8 mode);

void func_08058104(MenuWindow *window, u8 unitId, u8 mode, u8 row, u16 direction)
{
    u16 *buffer = data_02003CB0;
    u32 stride = window->width * 5;

    if (direction == 0x80) {
        func_0814186C(window->tiles + stride, buffer,
                      ((stride * 2 * sizeof(u16)) >> 1) & 0x1FFFFF);
        func_0814186C(buffer, window->tiles,
                      ((stride * 2 * sizeof(u16)) >> 1) & 0x1FFFFF);
        func_08057E98(window, row, unitId, mode);
    } else if (direction == 0x40) {
        func_0814186C(window->tiles, buffer,
                      ((stride * 2 * sizeof(u16)) >> 1) & 0x1FFFFF);
        func_0814186C(buffer, window->tiles + stride,
                      ((stride * 2 * sizeof(u16)) >> 1) & 0x1FFFFF);
        func_08057E98(window, row, unitId, mode);
    }
}
