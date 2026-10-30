#include "ffta.h"

typedef struct {
    void *manager;
    u8 unknown_04[0x10];
    void *tasks[16];
} State08121D0C;

extern State08121D0C *data_020159CC;

/* Complete [0x08121D0C, 0x08121D20), 20 bytes.
 * 03 49 09 68 80 00 14 31 09 18 08 68 70 47 00 00 CC 59 01 02
 */
void *func_08121D0C(u32 index)
{
    return data_020159CC->tasks[index];
}
