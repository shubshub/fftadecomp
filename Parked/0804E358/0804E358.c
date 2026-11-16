#include "ffta.h"

// Complete target [0x0804E358, 0x0804E3BA): 98 bytes, 41 instructions.
// 30b5041c2406240e0649a000064a801809680d1802f082fd042c07d102f07efd06e0
// 000048f501023c05000002f07efd0006020e06242988881d90420edd6b8858180006
// 000e904203d3a24201d2581e68802888002801d00138288030bc01bc0047
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

    func_08050E74();
    if (group == 4) {
        count = func_08050E74();
        rows = 6;
    } else {
        count = func_08050E84();
        rows = 6;
    }
    CLAMP_SELECTION(saved, count, rows);
}
