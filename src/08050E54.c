#include "ffta.h"

typedef struct {
    u8 unknown_00[0x79];
    u8 row;
} Menu08050E54;

extern u32 func_080504BC(Menu08050E54 *menu);
extern void func_080505BC(Menu08050E54 *menu, u8 row);

/* 0x08050E54 - 32 bytes.
 * Target: 10b5041cfff730fb0006002805d0201c79300178201cfff7a7fb10bc01bc0047
 */
void func_08050E54(Menu08050E54 *menu)
{
    if ((u8)func_080504BC(menu) != 0)
        func_080505BC(menu, menu->row);
}
