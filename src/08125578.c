/* func_08125578 - 0x08125578, 78 bytes + 4-byte literal pool
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  30b5 0006 010e ff29 12d1 084a 0023 8025 ed00 8424 6400 118d
 *           281c 0840 0028 0ed1 0133 1219 172b f6dd 0020 0de0 8000 0002
 *           0806 0028 05db 081c a2f70cff 04e0 101c 02e0 081c fcf77afb 30bc
 *           02bc 0847
 *   pool    02000080
 *
 * A selector byte is resolved to a record of the scene-record table at
 * 0x02000080.  0xFF is the wildcard: the table is scanned for the first
 * record whose flags word at +0x28 carries bit 0x400.  A negative selector
 * is looked up by func_08121CB4, a non-negative one by func_080C83CC, which
 * searches the same table plus the twelve records that follow it.
 *
 * The table address stays in a variable (`g_state_02000080` is read once into
 * a register and the scan walks it by the 0x108 record stride), so the ROM
 * needs a single literal pool entry for it.
 *
 * The record stride 0x108 and the mask 0x400 are both wider than a Thumb
 * immediate, so the ROM materialises them as 0x84 << 1 and 0x80 << 3.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 unknown_28;
    u8 unknown_2A[0x108 - 0x2A];
} SceneRecord;

typedef struct {
    SceneRecord first[24];
    u8 unknown_18C0[0x1684];
    SceneRecord second[12];
} State;

extern State g_state_02000080;

void *func_080C83CC(u8 category);
void *func_08121CB4(u8 index);

void *func_08125578(u8 selector)
{
    SceneRecord *record;
    s32 index;

    if (selector == 0xFF) {
        record = g_state_02000080.first;
        for (index = 0; index < 24; index++, record++) {
            if (record->unknown_28 & 0x400)
                return record;
        }
        return 0;
    } else if ((s8)selector < 0) {
        return func_08121CB4(selector);
    } else {
        return func_080C83CC(selector);
    }
}
