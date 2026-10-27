#include "ffta.h"

typedef struct TextSource08019814 TextSource08019814;

typedef struct {
    u32 unknown_00;
    const TextSource08019814 *selection;
} State08019814;

extern State08019814 g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *func_080CA1BC(const TextSource08019814 *source);
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete [0x08019814, 0x0801984A): 54 bytes, 20 instructions. */
u32 func_08019814(u8 *destination)
{
    const TextSource08019814 *selection = g_state_020020D0.selection;
    const u8 *text = func_080CA1BC(selection);

    if (selection == 0)
        func_08018C24(destination, g_table_08526680[0]);
    else
        func_08018C24(destination, text);
    return 0;
}
