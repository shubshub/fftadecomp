/* func_080112D4 - 0x080112D4, 20 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 448e 0c80 818e 1180 c08e 1880 10bc 01bc 0047
 *
 * Copies three halfwords out of a structure.  The fields sit at +0x32, +0x34
 * and +0x36, so the struct needs the padding in front of them for the
 * immediate offsets to come out right.
 */

#include "ffta.h"

void func_080112D4(Vec3 *src, s16 *a, s16 *b, s16 *c) {
    *a = src->x;
    *b = src->y;
    *c = src->z;
}