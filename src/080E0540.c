/* Target bytes: f0b5071c09040e0c0025b5420dd2a800c4192068002803d025f7fefa00202060681c0004050cb542f1d3f0bc01bc0047 */
#include "ffta.h"

void func_08005B58(void *object);

void func_080E0540(void **objects, u16 count)
{
    u16 index;

    for (index = 0; index < count; index++) {
        if (objects[index] != 0) {
            func_08005B58(objects[index]);
            objects[index] = 0;
        }
    }
}
