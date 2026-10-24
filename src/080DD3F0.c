#include "ffta.h"

/* 0x080DD3F0 - 66 bytes.
 * Target: 70b5061c60202df72df9051cb9f7befc291cbcf781fc0006040e0022a24209d29000
 *         8119401900680860501c0006020ea242f5d3281c2df71ff9201c70bc02bc0847
 */
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *pointer);
extern void *func_08096D7C(void);
extern u32 func_08099D08(void *context, void **list);

u8 func_080DD3F0(void **destination)
{
    void **list = func_0800A654(0x60);
    u8 count = func_08099D08(func_08096D7C(), list);
    u8 index;

    for (index = 0; index < count; index++)
        destination[index] = list[index];
    func_0800A668(list);
    return count;
}
