#include "ffta.h"

/* Target: complete [0x08121B78, 0x08121B8C), 20 bytes including literal. */
extern void *data_020159C4;
extern void func_08007170(void *, u8 *);

void func_08121B78(u8 *object)
{
    func_08007170(data_020159C4, object);
}
