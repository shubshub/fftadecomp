/* func_080DBC58 - 0x080DBC58, 44 bytes of code + a 4-byte literal pool
 *
 * Moves a 32-byte record between two slots of the table at 0x03003A60.
 *
 * func_08099C14 stores the byte it is handed into the byte at +0x1E of the
 * object and hands back the byte that was there, so `previous` is the record
 * the object was pointing at and `index` is the one it points at now.  The
 * table holds 32-byte records indexed by that byte.  The record the old
 * index selects is the copy source (r0) and the record the new index selects
 * is its destination (r1); the control word 0x10 is sixteen halfwords, one
 * whole record.
 *
 * The base address is written out at both uses on purpose.  It is not a
 * constant address - the index is a runtime value - so the two uses share one
 * literal pool entry, 0x03003A60.  Putting the base in a local pointer
 * instead hoists the load ahead of the shift and the bytes change.
 *
 *   target  30b50c06240e211cbdf7d8ff051c2d062d0e68010549401864016418211c
 *           102265f0f8fd281c30bc02bc0847603a0003
 */

#include "ffta.h"

typedef struct {
    u8 data[32];
} Record32;

/* Stores the byte at +0x1E of the object and returns the one that was there. */
extern u32 func_08099C14(void *object, u8 value);
/* The BIOS CpuSet (svc 0x0B): source, destination, control. */
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 func_080DBC58(void *object, u32 value) {
    u8 index = (u8)value;
    u8 previous = (u8)func_08099C14(object, index);
    u8 *source = ((Record32 *)0x03003A60)[previous].data;
    u8 *destination = ((Record32 *)0x03003A60)[index].data;

    func_0814186C(source, destination, 0x10);
    return previous;
}
