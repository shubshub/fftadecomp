#include "ffta.h"

/* Complete [0x08A38D24, 0x08A38E9E): 378 bytes, 187 instructions and one literal
 * word.  0808F74C copies this overlay to IWRAM.
 * f0b557464e464546e0b482b0041c04480078002800d0a8e0271c002f23d002e0285f0003071c
 * aa21490078180068002813d00178407802021e20c01984463b1c2e330a43002a08dd18786146
 * 0870013301208444013a002af6dcb4214900781800680028ded1271c002f7ed0391c3e310878
 * 002873d0aa225200b818006800286dd01432b81800688446002867d00091aa20400060440068
 * 002859d066463e363078002854d0a02040003a1861460b189168d86881424bdad16898688142
 * 47dd11685868814243da5168186881423fdd00213c1c40343d1c1e35009a1278914236dab046
 * 287801318946211c103101916a1c9246022824d000266246403263461e334046007886421bda
 * a168d068814210dae168906881420cdd21685068814208da61681068814204dd297818788842
 * 00d21970013610320133414609788e42e3db4946019c5546009a12789142c9dbb42040006044
 * 00688446002898d1b421490078180768002f80d102b038bc9846a146aa46f0bc01bc0047
 */

/* The count is read with two ldrb, lsls #8 and an orrs whose destination is
 * the high byte's register (0x08A38D56..0x08A38D66): the unaligned-halfword
 * order agbcc emits for a packed u16.  An explicit p[0] | p[1] << 8 leaves the
 * result in the low byte's register instead.  0808F638 reads the same header
 * the same way at 0x0808F6D6; 08138B4C is a matched packed-field precedent. */
typedef struct {
    u16 count;
} __attribute__((packed)) Header08A38D24;

/* (left, right) at +0 and (top, bottom) at +8 are min/max pairs: every test
 * compares one box's minimum against the other's maximum. */
typedef struct {
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
} Bounds08A38D24;

typedef struct Object08A38D24 {
    u8 unknown_000[0x1E];
    u8 layer[16];
    u8 base_layer[16];
    u8 part_count;
    u8 unknown_03F;
    Bounds08A38D24 parts[16];
    Bounds08A38D24 bounds;
    u8 unknown_150[4];
    const Header08A38D24 *data;
    u8 unknown_158[0x10];
    struct Object08A38D24 *next;
} Object08A38D24;

extern u8 data_03005F28;

/* The ROM repeats this four-compare test for the two bounding boxes
 * (0x08A38DD4..0x08A38DF2) and for each pair of parts (0x08A38E2E..0x08A38E4C). */
#define OVERLAPS(a, b) ((a)->top < (b)->bottom && (a)->bottom > (b)->top \
                        && (a)->left < (b)->right && (a)->right > (b)->left)

/* The ROM reads the count (0x08A38D56) before it forms the destination and
 * source addresses (0x08A38D5C..0x08A38D64) and finishes the count into the
 * loop counter after them (0x08A38D66): an inlined call evaluates its
 * arguments and then binds them to its parameters in that order. */
static inline void copy_bytes(u8 *dst, const u8 *src, s32 size)
{
    for (; size > 0; size--)
        *dst++ = *src++;
}

void func_08A38D24(Object08A38D24 *head)
{
    s32 i, j;
    Object08A38D24 *object;
    Object08A38D24 *other;
    Bounds08A38D24 *part;
    Bounds08A38D24 *other_part;
    u8 *layer;
    u8 *other_layer;

    if (data_03005F28)
        return;

    /* The exit test sits after the body and the advance after the exit test:
     * the entry branches past the loop-top copy (0x08A38D42) and the bottom
     * test loads next into r0 for the copy at 0x08A38D48.  0808F638 walks its
     * list the same way (0x0808F668, 0x0808F678). */
    object = head;
    if (object) {
        for (;;) {
            if (object->data)
                copy_bytes(object->layer, object->base_layer, object->data->count);
            if (object->next == 0)
                break;
            object = object->next;
        }
    }

    for (object = head; object; object = object->next) {
        if (object->part_count == 0 || object->data == 0)
            continue;
        for (other = object->next; other; other = other->next) {
            if (other->data == 0 || other->part_count == 0)
                continue;
            if (!OVERLAPS(&object->bounds, &other->bounds))
                continue;
            for (i = 0, part = object->parts, layer = object->layer;
                 i < object->part_count; i++, part++, layer++) {
                if (*layer == 2)
                    continue;
                for (j = 0, other_part = other->parts, other_layer = other->layer;
                     j < other->part_count; j++, other_part++, other_layer++) {
                    if (OVERLAPS(part, other_part) && *other_layer < *layer)
                        *other_layer = *layer;
                }
            }
        }
    }
}
