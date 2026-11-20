#include "ffta.h"

/* Complete [0x08A38EA0, 0x08A38FC8): 296 bytes: 141 instructions, a padding
 * halfword and three literal words.  0808F74C copies this overlay to IWRAM;
 * this function is installed at 0x030062EC and called through ROM slot
 * 0x08394028.  It walks a list of OAM pieces placed at (x, y), optionally
 * mirrored, and returns 1 as soon as one of them touches the 240x160 screen.
 * f0b557464e464546e0b48a46161c08991b061b0e98460906090e8c46841c0178407805020d43
 * 2804002873dd802040008146617889098900e0788009091889000e480b18a278e07801210840
 * 010211430a1c101c4f463840002804d00849081c02431004010c4246002a0bd0080400145746
 * 381a1988401a07e00000286d000300ffffff0804001450440004010c08040114002904da0022
 * 985e0818002832dbef2904dd0027d85f0818ef282bdc21780a1c80201040002805d080214942
 * 081c02431004010c6246002a05d008040014301a5988401a02e00804001480190004010c0804
 * 0114002904da0227d85f0818002808db9f2904dd0222985e08189f2801dc012007e02804064f
 * c0190634050c00288edc002038bc9846a146aa46f0bc02bc08470000ffff
 */

/* The count is read with two ldrb, lsls #8 and an orrs whose destination is
 * the high byte's register (0x08A38EBE..0x08A38EC4): a packed u16, as 08A38D24
 * reads the same kind of header at 0x08A38D56. */
typedef struct {
    u16 count;
} __attribute__((packed)) Header08A38EA0;

/* One list entry: the first two OAM attribute words and two more bytes, 6
 * bytes with no alignment.  x is read as a split field: ldrb [+2], then a
 * second ldrb [+3] (0x08A38EE6, although +3 was loaded at 0x08A38ED8 for the
 * size), ands #1, lsls #8 and an orrs into the high part's register.  Explicit
 * byte arithmetic shares the +3 load and leaves the result in the low byte's
 * register. */
typedef struct {
    u32 y : 8;
    u32 unknown_01 : 6;
    u32 shape : 2;
    u32 x : 9;
    u32 unknown_03 : 5;
    u32 size : 2;
    u16 unknown_04;
} __attribute__((packed)) Piece08A38EA0;

typedef struct {
    s16 width;
    s16 height;
} Size08A38EA0;

/* The OAM dimensions in pixels, indexed by shape * 4 + size; the last 64
 * bytes of the overlay image (ROM 0x08A398DC..0x08A3991C).  Shape 3 is zero. */
extern const Size08A38EA0 data_03006D28[16];

s32 func_08A38EA0(const u8 *data, s32 x, s32 y, u8 flip_x, u8 flip_y)
{
    const Piece08A38EA0 *piece;
    s16 count;
    const Size08A38EA0 *size;
    s16 px, py;

    piece = (const Piece08A38EA0 *)(data + 2);
    for (count = ((const Header08A38EA0 *)data)->count; count > 0; count--, piece++) {
        size = &data_03006D28[piece->shape * 4 + piece->size];

        px = piece->x;
        if (px & 0x100)
            px |= 0xFF00;
        if (flip_x)
            px = x - px - size->width;
        else
            px = px + x;
        if (px < 0 && px + size->width < 0)
            continue;
        if (px > 239 && px + size->width > 239)
            continue;

        py = piece->y;
        if (py & 0x80)
            py |= 0xFF80;
        if (flip_y)
            py = y - py - size->height;
        else
            py = py + y;
        if (py < 0 && py + size->height < 0)
            continue;
        if (py > 159 && py + size->height > 159)
            continue;

        return 1;
    }
    return 0;
}
