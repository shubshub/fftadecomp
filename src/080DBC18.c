/* func_080DBC18 - 0x080DBC18, 18 bytes
 *
 * A thin wrapper around func_08099C14: store a byte at +0x1E of the object
 * and hand back the byte that was there.
 *
 * func_08099C14 is exactly that - `ldrb r2,[r0,#0x1e]; strb r1,[r0,#0x1e];
 * mov r0,r2` - so this function is the call with the value narrowed to a
 * byte and the result narrowed to a byte as well.  The `lsls #24 / lsrs #24`
 * pair on the result is a zero extension, so the return type is unsigned
 * (an s8 would read back with `asrs`), and the `pop {r1}; bx r1` epilogue is
 * the non-void one.
 *
 * The value is taken wide and narrowed in a local, the same shape the
 * sibling func_080DBC58 uses - the mask then sits between the prologue and
 * the call, which is where the ROM has it.
 *
 * Every call site (0x08100E40, 0x0810C40A, 0x081183DA, 0x0811CCD2,
 * 0x0811CDBC) passes a byte in r1 and a pointer in r0.
 *
 *   target  00b50906090ebdf7f9ff0006000e02bc0847
 */

#include "ffta.h"

/* Stores the byte at +0x1E of the object and returns the one that was there. */
extern u32 func_08099C14(void *object, u32 value);

u8 func_080DBC18(void *object, u32 value) {
    u8 index = (u8)value;
    u8 previous = (u8)func_08099C14(object, index);
    return previous;
}
