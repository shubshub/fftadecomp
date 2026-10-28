#include "ffta.h"

typedef struct PaletteTransition PaletteTransition;

extern void func_081486C8(PaletteTransition *transition, u8 enabled, u8 flag40);
extern void func_08148600(PaletteTransition *transition);

/* Target: [0x081369EC, 0x08136A0E), 34 bytes, 14 instructions. */
void func_081369EC(PaletteTransition *transition)
{
    func_081486C8(transition, 1, 0);
    func_081486C8(transition, 1, 1);
    func_08148600(transition);
}
