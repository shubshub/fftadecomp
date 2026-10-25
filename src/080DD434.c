/* Target 0x080DD434, 66 bytes:
 * 70b5 061c 6020 2df70bf9 051c b9f79cfc 291c bcf775fc
 * 0006 040e 0022 a242 09d2 9000 8119 4019 0068 0860
 * 501c 0006 020e a242 f5d3 281c 2df7fdf8 201c 70bc 02bc 0847
 */
#include "ffta.h"

void *func_0800A654(u32 size);
void func_0800A668(void *object);
void *func_08096D7C(void);
u32 func_08099D34(void *context, void **objects);

u8 func_080DD434(void **destination)
{
    void **objects = func_0800A654(0x60);
    u8 count = func_08099D34(func_08096D7C(), objects);
    u8 index;

    for (index = 0; index < count; index++)
        destination[index] = objects[index];

    func_0800A668(objects);
    return count;
}
