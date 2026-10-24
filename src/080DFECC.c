#include "ffta.h"

extern void func_08005B58(void *task);

/* Target 0x080DFECC..0x080DFED6 (10 bytes):
 * 00 b5 25 f7 43 fe 01 bc 00 47
 */
void func_080DFECC(void *task)
{
    func_08005B58(task);
}
