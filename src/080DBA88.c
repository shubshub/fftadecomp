/* 0x080DBA88, 48 bytes
 * f0b5071c09060e0e0025b5420dd2a800c4192068002803d02af75af800202060681c0006050eb542f1d3f0bc01bc0047
 */
#include "ffta.h"

void func_08005B58(void *task);

void func_080DBA88(void **tasks, u8 count)
{
    u8 index;

    for (index = 0; index < count; index++) {
        if (tasks[index] != 0) {
            func_08005B58(tasks[index]);
            tasks[index] = 0;
        }
    }
}
