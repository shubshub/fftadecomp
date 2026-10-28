#include "ffta.h"

/* Complete target: [0x08053568, 0x080535BC), 84 bytes. */
typedef struct {
    u8 unknown_0000[0x1D48];
    u8 active[20];
} MenuState;

extern MenuState *data_0200F428;
extern u16 data_02001F3C[20];
extern u8 func_080CCA20(u16 entry);

void func_08053568(u8 *count, u8 *total)
{
    u16 *entries;
    u8 index;

    *count = 0;
    *total = 0;
    index = 0;
    entries = data_02001F3C;
    do {
        if (data_0200F428->active[index] == 1) {
            *total += func_080CCA20(entries[index]);
            (*count)++;
        }
        index++;
    } while (index < 20);
}
