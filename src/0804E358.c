#include "ffta.h"

/* Complete target [0x0804E358, 0x0804E3BA): 98 bytes, 41 instructions.
 * 30b5041c2406240e0649a000064a801809680d1802f082fd042c07d102f07efd06e0
 * 000048f501023c05000002f07efd0006020e06242988881d90420edd6b8858180006
 * 000e904203d3a24201d2581e68802888002801d00138288030bc01bc0047 */
typedef struct {
    u16 top;
    u16 selected;
} SavedSelection;

typedef struct {
    u8 unknown_000[0x53C];
    SavedSelection selections[1];
} MenuData;

extern MenuData *data_0201F548;
extern u8 func_08050E74(void);
extern u8 func_08050E84(void);

/* Pulls a saved list position back after the list's row count changed: when
 * the page runs past the count, the top row steps back one, and in a list
 * shorter than a page a selection at or past the end steps back with it.  The
 * ROM has the clamp once, at 0x0804E38E-0x0804E3B2.  It is a do { } while (0)
 * statement macro, the agbcc-era form of a multi-statement macro. */
#define CLAMP_SELECTION(saved, count, rows)                             \
    do {                                                                \
        if ((saved)->top + (rows) > (count)) {                          \
            if ((u8)((saved)->selected + (saved)->top) >= (count)       \
                    && (count) < (rows))                                \
                (saved)->selected--;                                    \
            if ((saved)->top)                                           \
                (saved)->top--;                                         \
        }                                                               \
    } while (0)

void func_0804E358(u8 group)
{
    SavedSelection *saved = &data_0201F548->selections[group];
    u8 count;
    u8 rows;

    /* The ROM makes this call and drops its result (bl at 0x0804E36C,
       before the group test at 0x0804E370); func_08050E74 only counts the
       active entries (func_08050C74 with a null output). */
    func_08050E74();
    /* Each list kind sets its own row count.  The ROM sets it once where
       the arms join (movs r4, #6 at 0x0804E38C) and compares the count with
       the register, not an immediate (cmp r2, r4 at 0x0804E3A2). */
    if (group == 4) {
        count = func_08050E74();
        rows = 6;
    } else {
        count = func_08050E84();
        rows = 6;
    }
    /* BUG: an empty list underflows the saved row.  With count 0 every row
       is at or past the end and 0 < rows, so a selected of 0 becomes 0xFFFF
       (subs r0, r3, #1 at 0x0804E3A6, strh at 0x0804E3A8).  It is reached
       when the menu removes the only entry of list 4 (func_0804D7E8 zeroes
       it, then calls this with group 4) or of list 5 (func_0804D840, through
       func_08038694, with group 5).  The category menu still offers the
       empty list (func_0804D6B0), and func_0804F948 restores the row
       without a check: the low byte, read as s8 (ldrsb at 0x0804FA46), goes
       to func_08017AF4 as -1 (bl at 0x0804FA4C) and, as 0xFF, to
       func_08017FB0 (bl at 0x0804FAA0).  docs/bugs/0804E358/ has the case. */
#ifdef BUGFIX
    /* An empty list has no row to step back to: leave the cursor on row 0,
       where a list that was never opened has it. */
    if (count == 0) {
        saved->top = 0;
        saved->selected = 0;
    } else
#endif
    CLAMP_SELECTION(saved, count, rows);
}
