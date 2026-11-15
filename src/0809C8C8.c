#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE];
    s16 value_0E;
    s16 value_10;
    u8 unknown_12[0xA];
    u8 flags;
    u8 direction;
} Record0809C8C8;

/* Complete [0x0809C8C8, 0x0809C9E8): 288 bytes, 144 instructions.
 * Target: f0b5021c0c1c137f0227022018400006050e002d00d07fe0507f022822d0022802dc012805d077e0032839d0042855d072e001261840002809d1d1890e25505f0b2801dc08191ae0181c304362e0191c31431177d089001bd081000400280fdcd58136e001260120184000280dd1d5890e20115e0c204042814203dd281bd08101204ae0181c304344e0191c31431177d0890019d08100040028f1dbd58118e0012601201840002809d1118a1025505f0b2801dc08191de0181c30432ae0191c31431177108a001b108200040028d7dc15820020507739431177d1e70120184000280cd1158a1020115e0c204042814202dd281b1082c3e7012018430ae0108a0019108200040028badb158200205077181c38431077b3e70020f0bc02bc0847
 */
s32 func_0809C8C8(Record0809C8C8 *record, s32 step)
{
    if (record->flags & 2) {
        return 0;
    }
    switch (record->direction) {
    case 1:
        if (!(record->flags & 1)) {
            if (record->value_0E < 12) {
                record->value_0E += step;
                return 1;
            }
            record->flags |= 1;
            return 1;
        }
        record->flags |= 1;
        record->value_0E -= step;
        if (record->value_0E > 0) {
            return 1;
        }
        record->value_0E = 0;
        record->direction = 0;
        record->flags |= 2;
        return 1;
    case 2:
        if (!(record->flags & 1)) {
            if (record->value_0E > -12) {
                record->value_0E -= step;
                return 1;
            }
            record->flags |= 1;
            return 1;
        }
        record->flags |= 1;
        record->value_0E += step;
        if (record->value_0E < 0) {
            return 1;
        }
        record->value_0E = 0;
        record->direction = 0;
        record->flags |= 2;
        return 1;
    case 3:
        if (!(record->flags & 1)) {
            if (record->value_10 < 12) {
                record->value_10 += step;
                return 1;
            }
            record->flags |= 1;
            return 1;
        }
        record->flags |= 1;
        record->value_10 -= step;
        if (record->value_10 > 0) {
            return 1;
        }
        record->value_10 = 0;
        record->direction = 0;
        record->flags |= 2;
        return 1;
    case 4:
        if (!(record->flags & 1)) {
            if (record->value_10 > -12) {
                record->value_10 -= step;
                return 1;
            }
            record->flags |= 1;
            return 1;
        }
        record->value_10 += step;
        if (record->value_10 < 0) {
            return 1;
        }
        record->value_10 = 0;
        record->direction = 0;
        record->flags |= 2;
        return 1;
    }
    return 0;
}
