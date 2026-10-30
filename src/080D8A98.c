#include "ffta.h"

extern void func_0801E6F0(u16 *first, u16 *second);

/* Complete target: [0x080D8A98, 0x080D8ACA), 50 bytes. */
void func_080D8A98(u16 *first_output, u16 *second_output)
{
    u16 first, second;

    func_0801E6F0(&first, &second);
    *first_output = (first & 7) + 8;
    *second_output = (second & 7) + 0x30;
}
