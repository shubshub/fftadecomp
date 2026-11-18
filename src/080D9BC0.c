#include "ffta.h"

extern void func_08141864(const void *source, void *destination, s32 count);

/* Complete target: [0x080D9BC0, 0x080D9BCC), 12 bytes.
 * Target bytes: 00b5a02267f04efe01bc0047
 * Apply one affine transform for each of the 160 display lines. */
void func_080D9BC0(const void *source, void *destination)
{
    func_08141864(source, destination, 160);
}
