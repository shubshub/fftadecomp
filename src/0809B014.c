#include "ffta.h"

/* Complete 0x0809B014..0x0809B11E: 266 bytes, 127 instructions.
 * f0b557464e464546e0b486b000900d1c92460e981b061b0e01930006000e0290009908682df002f90006000e0390ae78b146b04600220492002305930435012757453fda009880300068002169560122aa56fef7edfa041c002c0fd020682df0e5f80006000e039981423dd120682ff0b3f90a21a7f012fd002835d0aa78964201da161c0497904501dd904605974b46d11a019b18060016814225dc029b18060016814220db91462878697881f722fe0006000e02210840002815d1013704355745bfdb04980599884215d04246b11a002900da4942049b0598834206dd019a10060016814207dd012006e04942029b180600168142f7db002006b038bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    u8 x;
    u8 y;
    u8 value;
    u8 unknown_03;
} PathPoint;

typedef struct {
    void *unit;
    u8 unknown_04[0x7C];
    void *field;
} Actor;

typedef struct {
    void *unit;
} MapEntry;

extern u8 func_080C8240(void *data);
extern MapEntry *func_08099644(void *field, s8 x, s8 y);
extern s32 func_080CA3EC(const void *object);
extern u8 func_0801CD08(u8 column, u8 row);
extern u32 func_08142AB0(u32 value, u32 divisor);

s32 func_0809B014(Actor *actor, const PathPoint *points, s32 count,
                  s8 upper, s8 lower)
{
    u8 flag = func_080C8240(actor->unit);
    s32 maximum = points->value;
    s32 previous = maximum;
    s32 minimum = maximum;
    s32 maximum_index = 0;
    s32 minimum_index = 0;
    s32 index;
    s32 difference;

    points++;
    for (index = 1; index < count; index++, points++) {
        MapEntry *entry = func_08099644(actor->field, points->x, points->y);
        s32 value;
        u8 flags;

        if (entry != 0) {
            if (flag != func_080C8240(entry->unit))
                return 1;
            if (func_08142AB0(func_080CA3EC(entry->unit), 10) == 0)
                return 1;
        }
        value = points->value;
        if (maximum < value) {
            maximum = value;
            maximum_index = index;
        }
        if (minimum > value) {
            minimum = value;
            minimum_index = index;
        }
        difference = value - previous;
        if (difference > upper)
            return 1;
        if (difference < lower)
            return 1;
        previous = value;
        flags = func_0801CD08(points->x, points->y);
        if (flags & 2)
            return 1;
    }
    if (maximum_index != minimum_index) {
        difference = maximum - minimum;
        /* Never negative (maximum >= minimum), but the ROM still takes the
         * magnitude: cmp/bge/rsbs at 0x0809B0E4..0x0809B0E8. */
        if (difference < 0)
            difference = -difference;
        if (maximum_index > minimum_index) {
            if (difference > upper)
                return 1;
        } else if (-difference < lower) {
            return 1;
        }
    }
    return 0;
}
