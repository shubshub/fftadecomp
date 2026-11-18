#include "ffta.h"

typedef struct ScanlineEffect ScanlineEffect;

extern void func_0800C720(ScanlineEffect *effect, u16 *destination, u8 stride);

void func_0800DDB0(void *effect, u16 *destination)
{
    func_0800C720(effect, destination, 2);
}
