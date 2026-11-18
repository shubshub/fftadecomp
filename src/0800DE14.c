#include "ffta.h"

typedef struct ScanlineEffect ScanlineEffect;

extern void func_0800C804(ScanlineEffect *effect, u16 *destination, u8 stride);

void func_0800DE14(void *effect, u16 *destination)
{
    func_0800C804(effect, destination, 2);
}
