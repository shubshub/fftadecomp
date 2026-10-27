#include "ffta.h"

typedef struct PaletteTransition PaletteTransition;

extern void func_08148704(PaletteTransition *transition, u8 enabled, u8 index);
extern void func_08148600(PaletteTransition *transition);

/* Complete [0x0813DAFC, 0x0813DB32): 54 bytes, 22 instructions. */
void func_0813DAFC(PaletteTransition *transition)
{
    func_08148704(transition, 1, 0);
    func_08148704(transition, 1, 1);
    func_08148704(transition, 1, 2);
    func_08148704(transition, 1, 3);
    func_08148600(transition);
}
