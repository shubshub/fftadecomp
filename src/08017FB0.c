/* func_08017FB0 - 0x08017FB0, 12 bytes (0x08017FB0 .. 0x08017FBC)
 *
 * target  0906 090e 4174 0901 c181 7047
 *
 * The index span in config/functions.json is right this time: the function
 * ends at the `bx lr` in 0x08017FBA..0x08017FBB and 0x08017FBC is the next
 * function (a two-byte `bx lr` of its own, called from 0x080093C0 and
 * 0x0802845E).
 *
 * It is the record family the sibling functions use (see src/08017D18.c and
 * src/08017C28.c): +0x00 is a word, +0x04 the owner pointer, +0x08/+0x0A/
 * +0x0C/+0x0E are halfwords and +0x10/+0x11/+0x12 are bytes.  This function
 * writes two of them:
 *
 *   +0x11 (byte)   the argument,
 *   +0x0E (halfword) the same argument shifted up by four.
 *
 * The argument is a byte: the callers pass one (a `ldrb`, or a value already
 * masked with `lsls #24 / lsrs #24`), and the `lsls #24 / lsrs #24` pair at
 * the top of the body is the zero-extension of that byte to the int it is
 * shifted in - the byte store itself needs no conversion.  Because the
 * argument is known to be a byte, the shift is at most 0xFF0, so the halfword
 * store needs no masking either and the body is frameless: six instructions,
 * no pool, no saved registers, plain `bx lr`.
 */

#include "ffta.h"

typedef struct {
    u32  unknown_00;
    void *owner;       /* +0x04 */
    u16  field_08;
    u16  field_0a;
    u16  field_0c;
    u16  unknown_0e;   /* +0x0E - written here */
    u8   field_10;
    u8   unknown_11;   /* +0x11 - written here */
    u8   field_12;
} State08017FB0;

void func_08017FB0(State08017FB0 *s, u8 value) {
    s->unknown_11 = value;
    s->unknown_0e = value << 4;
}
