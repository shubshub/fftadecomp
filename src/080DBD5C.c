/* func_080DBD5C - 0x080DBD5C, 20 bytes
 *
 * Copies three s16 fields out of a structure - the same shape as
 * func_08011040, but the triple starts at +8 instead of +0x1e, so it is a
 * different structure.  Matched with: agbcc -mthumb-interwork -O2
 *
 *   target  10b5 0489 0c80 4189 1180 8089 1880 10bc 01bc 0047
 */

#include "ffta.h"

void func_080DBD5C(Struct080DBD5C *source, s16 *first, s16 *second, s16 *third) {
    *first = source->x;
    *second = source->y;
    *third = source->z;
}
