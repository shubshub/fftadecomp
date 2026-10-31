#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA];
    u16 x;
    u16 y;
} SecondaryViewport;

typedef struct {
    u8 unknown_00[0x24];
    u16 focusX;
    u16 focusY;
    u8 unknown_28[0x228 - 0x28];
    SecondaryViewport secondary;
} ViewportState;

extern ViewportState g_state_02007F40;
extern void func_0801D918(void);

/* Complete target [0x0801D8E8, 0x0801D918): 48 bytes, 19 instructions.
 * 10b5094909480b18988c083808246442221c10404881d88c30381040888100f007f8
 * 10bc01bc004768810002d8fdffff
 */
void func_0801D8E8(void)
{
    SecondaryViewport *secondary = &g_state_02007F40.secondary;

    secondary->x = (g_state_02007F40.focusX - 8) & ~7;
    secondary->y = (g_state_02007F40.focusY - 48) & ~7;
    func_0801D918();
}
