#include "ffta.h"

/* Complete [0x08A3915C, 0x08A39458): 764 bytes, 352 instructions and 14
 * literal words.  0808F74C copies this overlay to IWRAM; this function is
 * installed at 0x030065A8 and called through ROM slot 0x0839402C (by
 * 0808F638 and 0808F1F4, which draw the objects of the render tree).  An
 * OAM list builder that takes the current OAM buffer itself: it appends the
 * visible pieces of a piece list placed at (x, y), optionally mirrored, to
 * the buffer's entries, up to `limit` new entries (0 for no limit of its
 * own), and stores the new entry count back.  08A397D8 is the same front
 * end around the out-of-line worker 08A39458.
 * f0b557464e464546e0b488b0051c0091019210981199129a139c179eb1461b061b0e02930006
 * 000e03900906090e04911206120e05922406240e0694002e11d00649074a1078800040180068
 * 81444846802809dd8021894606e00000200000032800000380229146214b1878820221498000
 * 214e8019159b0793531800688046c84500db1de1c0001b18ae1c297868780002824608438246
 * 0004002800dc10e1717889098900f07880090918890013480d18b178f0780122104002020a43
 * 111c802040000840002804d00d4a101c01430804020c0598002814d0100400140099081a2988
 * 401a0004020c081c11e00000280000033000000320000003286d000300ffffff10040014009a
 * 80180004020c288811040a1410180004000c041c8c46002a03da0004002800dabde0ef2a04dd
 * 20040014ef2800ddb6e03078041c211c80200840271c002805d080225242101c01430804040c
 * 0698002808d0200400140199081a6988401a0004040c06e020040014019a80180004040c6988
 * 60460014844640180004010c0d1c20040214002a03da0804002800da86e09f2a04dd28040014
 * 9f2800dd7fe070780002384319881880b178f078000208435988588031797079000208439988
 * 988002990322114089005a780d20404210400843587003990120014009015a78123810400843
 * 587004990122114049015a782120404210400843587018781c70d978c906c90f059841400122
 * 11400901da781120404210400843d870d9788906c90f06984140012211404901da7821204042
 * 10400843d8702749081c614601405a88264810400843588099888905890d149a8918224a101c
 * 01409a88214810400843988059790907890f0798007809180322114089005a790d2040421040
 * 08435871597909091698091809015a790f20104008435871083301218844c8450cda52461004
 * 104940180636079a01320792010c8a46002800ddeee60c4a107880000b4bc0184646066008b0
 * 38bc9846a146aa46f0bc01bc0047ff01000000feffffff03000000fcffff0000ffff28000003
 * 20000003
 */

/* The count is read with two ldrb, lsls #8 and an orrs whose destination is
 * the high byte's register (0x08A391E8..0x08A391F0): a packed u16, as
 * 08A38D24 and 08A38EA0 read the same header. */
typedef struct {
    u16 count;
} __attribute__((packed)) Header08A3915C;

/* One list entry: the three OAM attribute words, 6 bytes with no alignment
 * (08A38EA0 reads the same entries).  x is read as a split field (ldrb [+2],
 * a second ldrb [+3], ands #1, lsls #8, orrs: 0x08A3920E..0x08A39218).  The
 * words are read whole for the copy at 0x08A39304..0x08A39324, each as two
 * bytes with the high byte's register as the orrs destination. */
typedef union {
    struct {
        u32 y : 8;
        u32 unknown_01 : 6;
        u32 shape : 2;
        u32 x : 9;
        u32 unknown_03 : 5;
        u32 size : 2;
        u16 unknown_04;
    } __attribute__((packed)) field;
    struct {
        u16 attr0;
        u16 attr1;
        u16 attr2;
    } __attribute__((packed)) word;
} __attribute__((packed)) Piece08A3915C;

/* One entry of the OAM buffer, 8 bytes.  Every access to it in the ROM is a
 * separate load or store, which is the volatile qualifier:
 * - each whole-word store is preceded by a load of the same word whose value
 *   is not used (ldrh at 0x08A3930A, 0x08A39316 and 0x08A39322), and so is
 *   the byte store of y (ldrb at 0x08A39360);
 * - each read-modify-write of a field loads its unit twice, once for the old
 *   value and once for the insertion (+3 at 0x08A39364/0x08A39374 and
 *   0x08A39380/0x08A39390, +4 at 0x08A393AE/0x08A393BE, +5 at
 *   0x08A393C8/0x08A393DA and 0x08A393E6/0x08A393F0);
 * - each field is stored on its own although a later store rewrites the
 *   same unit (+1 at 0x08A39338 and 0x08A3934A before 0x08A3935E, +3 at
 *   0x08A3937E before 0x08A3939A, +5 at 0x08A393E4 before 0x08A393F8), and
 *   attr2 is stored whole at 0x08A39324 before its fields are rewritten.
 * Without the qualifier agbcc deletes the unused loads, shares the others
 * and drops the overwritten stores.  data_03000030 holds the two banks of
 * these entries; the OAM flush 080012BC hands the inactive one to DMA0
 * (0x080013D4 stores its address to DMA0SAD).  include/control_flags.h
 * declares the LCD register image, the other RAM copy of hardware state,
 * volatile on the same evidence. */
typedef volatile union {
    struct {
        u32 y : 8;
        u32 unknown_01_0 : 2;
        u32 mode : 2;
        u32 mosaic : 1;
        u32 bpp : 1;
        u32 unknown_01_6 : 2;
        u32 x : 9;
        u32 unknown_03_1 : 3;
        u32 flip_x : 1;
        u32 flip_y : 1;
        u32 unknown_03_6 : 2;
        u16 tile : 10;
        u16 priority : 2;
        u16 palette : 4;
        u16 unknown_06;
    } field;
    struct {
        u16 attr0;
        u16 attr1;
        u16 attr2;
        u16 unknown_06;
    } word;
} Oam08A3915C;

typedef struct {
    s16 width;
    s16 height;
} Size08A3915C;

/* The OAM dimensions in pixels, indexed by shape * 4 + size; the last 64
 * bytes of the overlay image (ROM 0x08A398DC..0x08A3991C). */
extern const Size08A3915C data_03006D28[16];

extern u8 data_03000028;
extern Oam08A3915C data_03000030[2][0x80];
extern s32 data_03000020[2];

/* The worker is an inlined function, as 08A39458 is 08A397D8's out-of-line
 * one.  The ROM binds the arguments in parameter order after it has
 * evaluated them: the buffer address and the count's address are formed at
 * 0x08A391C4..0x08A391D0, then `priority` is copied to its own slot
 * (0x08A391D2), then the buffer pointer is completed (0x08A391D6) and the
 * count loaded (0x08A391D8).  The return inside the loop is the second sign:
 * with two exits agbcc keeps the size table's address load in the loop body
 * (0x08A3920A, in r0), where a loop with one exit has it reloaded into r2. */
static inline s32 append_pieces(const u8 *data, s32 x, s32 y, u8 mode,
                                u8 mosaic, u8 bpp, u8 flip_x, u8 flip_y,
                                s32 tile, const u8 *priority, s32 palette,
                                Oam08A3915C *oam, s32 limit, s32 count)
{
    const Piece08A3915C *piece;
    s16 n;
    const Size08A3915C *size;
    s16 px, py;
    s16 right, bottom;

    if (count < limit) {
        oam += count;
        piece = (const Piece08A3915C *)(data + 2);
        for (n = ((const Header08A3915C *)data)->count; n > 0;
             n--, piece++, priority++) {
            size = &data_03006D28[piece->field.shape * 4 + piece->field.size];

            px = piece->field.x;
            if (px & 0x100)
                px |= 0xFF00;
            if (flip_x)
                px = x - px - size->width;
            else
                px = px + x;
            right = px + size->width;
            if (px < 0 && right < 0)
                continue;
            if (px > 239 && right > 239)
                continue;

            py = piece->field.y;
            if (py & 0x80)
                py |= 0xFF80;
            if (flip_y)
                py = y - py - size->height;
            else
                py = py + y;
            /* BUG: the bottom edge is taken from px, not py (0x08A392D8:
             * the px kept in ip is added to the height).  A piece above or
             * below the screen is then kept or dropped by where it is
             * horizontally: a 32x8 piece at (-20, -4) reaches rows 0..3 but
             * is dropped because -20 + 8 < 0, and a 64x64 piece at (10, 200)
             * is kept because 10 + 64 <= 159; its y wraps at 256 and its
             * last rows show in rows 0..7.  08A38EA0 and 08A39458 add the
             * height to py.  docs/bugs/08A3915C/ has the case. */
#ifdef BUGFIX
            bottom = py + size->height;
#else
            bottom = px + size->height;
#endif
            if (py < 0 && bottom < 0)
                continue;
            if (py > 159 && bottom > 159)
                continue;

            oam->word.attr0 = piece->word.attr0;
            oam->word.attr1 = piece->word.attr1;
            oam->word.attr2 = piece->word.attr2;
            oam->field.mode = mode;
            oam->field.mosaic = mosaic;
            oam->field.bpp = bpp;
            oam->field.y = py;
            oam->field.flip_x ^= flip_x;
            oam->field.flip_y ^= flip_y;
            oam->field.x = px;
            oam->field.tile += tile;
            oam->field.priority += *priority;
            oam->field.palette += palette;
            oam++;
            count++;
            if (count >= limit)
                return count;
        }
    }
    return count;
}

void func_08A3915C(const u8 *data, s32 x, s32 y, u8 mode, u8 mosaic, u8 bpp,
                   u8 flip_x, u8 flip_y, s32 tile, const u8 *priority,
                   s32 palette, s32 limit)
{
    Oam08A3915C *entries;
    s32 count;

    if (limit) {
        limit += data_03000020[data_03000028];
        if (limit > 128)
            limit = 128;
    } else {
        limit = 128;
    }

    entries = data_03000030[data_03000028];
    count = data_03000020[data_03000028];
    data_03000020[data_03000028] = append_pieces(data, x, y, mode, mosaic,
        bpp, flip_x, flip_y, tile, priority, palette, entries, limit, count);
}
