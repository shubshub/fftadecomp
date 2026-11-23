#include "ffta.h"

/* Complete [0x0809836C, 0x080989AC): 1600 bytes, 627 instructions.
 * Target:
 * f0b557464e464546e0b486b0061c0904090c8a4612061b041f0c100e8046002a
 * 01daf17f8846002291460020039000210491002452460b2a00d984e190000249
 * 4018006887460000b8830908ee830908188509087885090806860908d8850908
 * 34860908b2860908b2860908b2860908ee830908e883090896840908301cfff7
 * a1fe404607064c218919884644460022914601252168002904d0306c89f7e4fb
 * 484620600434013d002df3da3a16301c00210123fff7dcf8706c802149000222
 * 89f7dafc444601252068002804d080214900022289f7d0fc0434013d002df3da
 * 306bc0210840002803d15146092900d09ce2f08e002803d1706c012189f7defc
 * 706c00218022520089f7b6fc444601252068002804d000218022520089f7acfc
 * 0434013d002df3da80e2424617064c2080198046444600218946012521680029
 * 04d0306c89f790fb4a4622600434013d002df3da30680079202808d0202802dc
 * 1d2804d005e0492803dc482801db042100e000210904090c3a16301c0023fff7
 * 77f8706c00218122520089f775fc444601252068002804d000218122520089f7
 * 6bfc0434013d002df3da3fe2404607064c218919884644460022914601252168
 * 002904d0306c89f74ffb484620600434013d002df3da3a16301c04210123fff7
 * 47f8706c00218122520089f745fc444601252068002804d000218122520089f7
 * 3bfc0434013d002df3da0fe241460f064c229219904644460020814601252168
 * 002904d0306c89f71ffb494621600434013d002df3da3a16301c40210123fff7
 * 17f8706c00218122520089f715fc444601252068002804d000218122520089f7
 * 0bfc0434013d002df3dadfe142461706341c4c340020804601252168002904d0
 * 306c89f7f1fa414621600434013d002df3da3a16301c442151e042461706341c
 * 4c340020804601252168002904d0306c89f7dafa414621600434013d002df3da
 * 3a16301c48213ae0424617064c208019804644460021894601252168002904d0
 * 306c89f7c1fa4a4622600434013d002df3da306b4021084000281dd03a16301c
 * 08210123fef7b4ff706c00218022120289f7b2fb444601252068002804d00021
 * 8022120289f7a8fb0434013d002df3da706c89f7e3fb79e13a16301c08210123
 * fef796ff72e1002f02d101256d420ee0381c032132f070f8051c381c092132f0
 * 6bf80390381c082132f066f88146681e12283bd8800002494018006887460000
 * f08609083c8709083c8709083c8709083c8709083c8709083c8709083c870908
 * 408709083c8709084c8709084c8709084c870908448709084487090840870908
 * 4c87090854870908508709084887090801250ce002250ae0032508e0042506e0
 * 052504e0062502e0072500e00025504606380b2800d99fe08000024940180068
 * 8746000074870908a4870908e487090824880908a4880908a4880908a4880908
 * 648809087688090886880908868809088c8809089088090800200490681e0428
 * 18d880000149401800688746bc870908d0870908d4870908d887090858880908
 * dc870908502467e05c2465e0682463e0742461e030245fe004210491681e0428
 * 18d880000149401800688746fc87090810880908148809081888090858880908
 * 1c880908542447e0602445e06c2443e0782441e034243fe008220492681e0428
 * 18d8800001494018006887463c88090850880908548809085888090858880908
 * 5c880908582427e0642425e0702423e07c2421e038241fe03024b92003900021
 * 049101250222914616e03024b9200390042104910125a9460ee01c2400250be0
 * 942400e098240125102204927e2003902d2f01d17c210391211c424610060716
 * 3a1c301c0123fef793fe002d32d1032080460125e719341c4c34306c6b1e2168
 * 134a9b181b78b28e009201970295012288f79cfe021c01204042824212d02260
 * b17f894650460d2801d10121894650460c2801d10221894648460106090e101c
 * 89f7aafa043401354545d6db3ee000005243390802218846306b0840002801d0
 * 012290460025454530da0498c019059050460c380004070c306caa00311c4c31
 * 8c182168154aaa181378039a0092059a01920295012288f759fe011c01204042
 * 814210d02160002d01dd06208146012f03d8081c012189f741f920684a461106
 * 090e89f769fa01354545d5db06b038bc9846a146aa46f0bc01bc004750433908
 */

typedef struct {
    u8 unknown_00[4];
    u8 category;
} Unit0809836C;

typedef struct {
    Unit0809836C *unit;
    u8 unknown_04[0x1A];
    u8 palette;
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u16 sprite;
    u16 animation;
    u8 unknown_38[8];
    void *renderer;
    u32 *display;
    u32 unknown_48;
    void *handles[2];
} Object0809836C;

extern const u8 data_08394350[];
extern const u8 data_08394352[];

extern void func_08098130(Object0809836C *object);
extern void func_080975DC(Object0809836C *object, u16 animation, s8 direction, s32 automatic);
extern void func_08021BD4(void *renderer, void *handle);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);
extern void func_08021E28(void *resource, u32 value);
extern void func_08021E68(u32 *flags);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern void *func_08021618(void *renderer, void *handle, u32 alternate, u32 second,
                           u32 category, u32 selector, u32 index);
extern void func_08021E64(void *handle, u8 palette);
extern void func_08021C08(void *handle, u8 enabled);

/* An inlined copy of func_0809A09C (src/0809A09C.c): every case of the first
 * switch releases both handles first (0x080983F8-0x08098416 and so on). */
static inline void inlined_0809A09C(Object0809836C *slots)
{
    s32 i;

    for (i = 0; i < 2; ++i) {
        if (slots->handles[i] != 0) {
            func_08021BD4(slots->renderer, slots->handles[i]);
            slots->handles[i] = 0;
        }
    }
}

/* An inlined copy of func_0809A570, with the masks taken as u16 parameters
 * and passed straight on.  Each inlined call loads its mask constants
 * afresh, also inside the loop (0x08098426-0x0809843E,
 * 0x080984F0-0x08098508).  src/0809A570.c spells the function with u32
 * parameters copied into u16 locals; both spellings compile to the same 58
 * bytes at 0x0809A570, but inlined here that one loads each mask once and
 * keeps it in a register across the loop (1632 bytes). */
static inline void inlined_0809A570(Object0809836C *flags, u16 clear, u16 set)
{
    s32 index;

    func_08021DE4(flags->display, clear, set);
    for (index = 0; index < 2; index++) {
        if (flags->handles[index] != 0)
            func_08021DE4(flags->handles[index], clear, set);
    }
}

/* An inlined copy of func_0809A298 (src/0809A298.c), as src/0809A2D8.c
 * inlines it.  The direction is bound to the helper's s8 parameter before
 * the call is set up: r2 is loaded ahead of r0 at 0x080988AC. */
static inline void inlined_0809A298(Object0809836C *object, u16 value, s8 adjustment)
{
    func_080975DC(object, value, adjustment, 1);
}

/* An inlined copy of func_0809A398 (src/0809A398.c), at 0x080984C0. */
static inline u32 inlined_0809A398(const void *object)
{
    const Unit0809836C *state = object;

    switch (state->category) {
    case 0x1D:
    case 0x20:
    case 0x48:
    case 0x49:
        return 4;
    default:
        return 0;
    }
}

/* Starts an action animation on a unit's sprite.  A negative direction keeps
 * the current one.  Actions 6-8 and 12-17 also attach the held item's
 * sprites, or the plain body sprites when the item has no weapon class. */
void func_0809836C(Object0809836C *object, u16 action, s8 direction, u16 item)
{
    s32 palette;
    s32 sprite;
    s32 offset;
    /* Wider than the u16 it is passed as: the narrowing's copy into r1 sits
     * ahead of the direction's sign extension (0x080988A4). */
    s32 animation;
    s32 category;
    s32 type;
    s32 count;
    s32 i;

    if (direction < 0)
        direction = object->direction;

    palette = 0;
    sprite = 0;
    offset = 0;
    animation = 0;

    switch (action) {
    case 10:
        func_08098130(object);
        /* Falls through: 0x080983E8 runs into case 0 at 0x080983EE. */
    case 0:
    case 9:
        inlined_0809A09C(object);
        inlined_0809A298(object, 0, direction);
        inlined_0809A570(object, 0x100, 2);
        if ((object->flags & 0xC0) || action == 9) {
            if (object->animation == 0)
                func_08021E28(object->display, 1);
            inlined_0809A570(object, 0, 0x100);
        }
        break;
    case 11:
        inlined_0809A09C(object);
        func_080975DC(object, inlined_0809A398(object->unit), direction, 0);
        inlined_0809A570(object, 0, 0x102);
        break;
    case 1:
        inlined_0809A09C(object);
        inlined_0809A298(object, 4, direction);
        inlined_0809A570(object, 0, 0x102);
        break;
    case 2:
        inlined_0809A09C(object);
        inlined_0809A298(object, 0x40, direction);
        inlined_0809A570(object, 0, 0x102);
        break;
    case 4:
        inlined_0809A09C(object);
        inlined_0809A298(object, 0x44, direction);
        break;
    case 3:
        inlined_0809A09C(object);
        inlined_0809A298(object, 0x48, direction);
        break;
    case 5:
        inlined_0809A09C(object);
        if (object->flags & 0x40) {
            inlined_0809A298(object, 8, direction);
            inlined_0809A570(object, 0, 0x8000);
            func_08021E68(object->display);
        } else {
            inlined_0809A298(object, 8, direction);
        }
        break;
    default:
        if (item == 0) {
            category = -1;
        } else {
            category = func_080CA7A4(item, 3);
            sprite = func_080CA7A4(item, 9);
            palette = func_080CA7A4(item, 8);
        }
        switch (category) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
            type = 1;
            break;
        case 8:
        case 15:
            type = 2;
            break;
        case 13:
        case 14:
            type = 3;
            break;
        case 19:
            type = 4;
            break;
        case 10:
        case 11:
        case 12:
        case 16:
            type = 5;
            break;
        case 18:
            type = 6;
            break;
        case 17:
            type = 7;
            break;
        default:
            type = 0;
            break;
        }
        switch (action) {
        case 6:
            offset = 0;
            switch (type) {
            case 1:
                animation = 0x50;
                break;
            case 2:
                animation = 0x5C;
                break;
            case 3:
                animation = 0x68;
                break;
            case 4:
                animation = 0x70;
                break;
            case 5:
                animation = 0x74;
                break;
            default:
                animation = 0x30;
                break;
            }
            break;
        case 7:
            offset = 4;
            switch (type) {
            case 1:
                animation = 0x54;
                break;
            case 2:
                animation = 0x60;
                break;
            case 3:
                animation = 0x6C;
                break;
            case 4:
                animation = 0x70;
                break;
            case 5:
                animation = 0x78;
                break;
            default:
                animation = 0x34;
                break;
            }
            break;
        case 8:
            offset = 8;
            switch (type) {
            case 1:
                animation = 0x58;
                break;
            case 2:
                animation = 0x64;
                break;
            /* Type 3 steps 0x68, 0x6C, 0x70 over actions 6-8 and type 4 is
             * 0x70 for all three; the ROM keeps one block for every 0x70
             * (0x08098858). */
            case 3:
                animation = 0x70;
                break;
            case 4:
                animation = 0x70;
                break;
            case 5:
                animation = 0x7C;
                break;
            default:
                animation = 0x38;
                break;
            }
            break;
        case 12:
            animation = 0x30;
            sprite = 0xB9;
            offset = 0;
            type = 1;
            palette = 2;
            break;
        case 13:
            animation = 0x30;
            sprite = 0xB9;
            offset = 4;
            type = 1;
            palette = 1;
            break;
        case 14:
        case 15:
            animation = 0x1C;
            type = 0;
            break;
        /* Cases 16 and 17 differ only in the animation; the ROM keeps
         * one copy of the rest (0x08098892). */
        case 16:
            animation = 0x94;
            type = 1;
            offset = 0x10;
            sprite = 0x7E;
            if (item == 0x2D)
                sprite = 0x7C;
            break;
        case 17:
            animation = 0x98;
            type = 1;
            offset = 0x10;
            sprite = 0x7E;
            if (item == 0x2D)
                sprite = 0x7C;
            break;
        }
        inlined_0809A298(object, animation, direction);
        if (type == 0) {
            count = 3;
            for (i = 1; i < count; i++) {
                void *handle = func_08021618(object->renderer, object->handles[i - 1], 1,
                                             data_08394352[i - 1], object->sprite,
                                             animation + direction, i);

                if (handle != (void *)-1) {
                    object->handles[i - 1] = handle;
                    palette = object->palette;
                    /* Actions 12 and 13 always set type 1, so these two
                     * tests never fire; the ROM keeps both
                     * (0x080988F0-0x08098902). */
                    if (action == 13)
                        palette = 1;
                    if (action == 12)
                        palette = 2;
                    func_08021E64(handle, palette);
                }
            }
        } else {
            count = 2;
            if (object->flags & 2)
                count = 1;
            for (i = 0; i < count; i++) {
                void *handle = func_08021618(object->renderer, object->handles[i], 1,
                                             data_08394350[i], sprite, offset + direction, i);

                if (handle != (void *)-1) {
                    object->handles[i] = handle;
                    if (i > 0)
                        palette = 6;
                    if (action == 12 || action == 13)
                        func_08021C08(handle, 1);
                    func_08021E64(object->handles[i], palette);
                }
            }
        }
        break;
    }
}
