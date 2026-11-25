#include "ffta.h"

/* Complete [0x081492D0, 0x08149368): 152 bytes, 67 instructions and three
 * literal words.
 * f0b557464e464546e0b489461206120e90461b061f0e051c024e5c2040428019824615e0
 * 646100031820001b800051464218311c5b3940180178090112788918c800401a28188078
 * 4006400e0f2808d0281c311c42463b1cfff770fb041c002ce2da484600280ad0094b1821
 * 091b890008480918a2001b684846f8f781ff201c38bc9846a146aa46f0bc02bc08470000
 * bcd4360808610003
 * Traces the path that ends at (x, y) back to its start with func_08148A0C
 * (src/08148A0C.c), which writes it backwards from data_03006108[23], and
 * copies the points to output when it is given.  Returns the point count, or
 * -1 when (x, y) was not reached. */

/* The search records of src/08148B60.c. */
typedef struct {
    u8 direction : 7;
    u8 valid : 1;
    u8 climb;
    u8 cost;
    u8 x : 7;
    u8 wide : 1;
    u8 y;
} __attribute__((packed)) PathNode;

typedef struct {
    u8 value : 7;
    u8 enabled : 1;
    u8 mode : 4;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 unknown_flag : 1;
    PathNode node;
} __attribute__((packed)) PathCell;

typedef struct {
    PathCell grid[16 * 16];
    PathNode queue[128];
    u8 category : 7;
    u8 active : 1;
    s8 max_climb;
    s8 max_drop;
    u8 max_cost;
    s8 scan_x;
    s8 scan_y;
    u8 start_x;
    u8 start_y;
    u8 head;
    u8 tail;
} __attribute__((packed)) PathState;

/* A traced point, as func_08148A0C writes it.  Byte aligned like the
 * records above: the ROM addresses y from the constant data_03006108 + 1
 * (0x03006164 - 0x5B at 0x08149302-0x08149306) and x from data_03006108
 * (sl), not as one element address with y at offset 1. */
typedef struct {
    u8 x;
    u8 y;
    u8 value;
    u8 wide;
} __attribute__((packed)) PathPoint;

typedef void (*BufferCopier)(void *destination, const void *source,
                             u32 size);

extern PathPoint data_03006108[24];
/* Entry 1 of the table at 0x0836D4B8, whose entry 0 the ROM loads again for
 * each call (src/08135984.c, src/0813F438.c): not const. */
extern BufferCopier data_0836D4BC[];

extern int func_08148A0C(PathCell *grid, PathPoint *output, u8 start_x,
                         u8 start_y);

/* The object is taken untyped, as src/08148B60.c and src/08149368.c take
 * it: the ROM copies it to r5 after narrowing x and y (0x081492E6). */
s32 func_081492D0(void *object, PathPoint *output, u8 x, u8 y)
{
    PathState *state = object;
    s32 count;

    /* Traces until the first point is the start cell (direction 15).  The
     * trace stops short of the start only at a flag6 cell (src/08148A0C.c),
     * and every call has the same arguments; the setter of flag6,
     * src/08149194.c, has no caller in the ROM.  The cell index is
     * x + y * 16: the ROM forms x's address first (0x08149300). */
    while ((count = func_08148A0C(state->grid, &data_03006108[23], x, y)) >= 0) {
        if (state->grid[data_03006108[24 - count].x
                        + data_03006108[24 - count].y * 16].node.direction == 15)
            break;
    }
    if (output) {
        /* Called through the table, as src/0804EBD0.c calls it: the ROM
         * loads the table's address ahead of the source (0x08149338) and
         * the entry after the size (0x08149346). */
        data_0836D4BC[0](output, &data_03006108[24 - count],
                         count * sizeof(PathPoint));
    }
    return count;
}
