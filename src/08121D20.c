#include "ffta.h"

typedef struct {
    void *manager;
    u8 unknown_04[0x10];
    void *tasks[16];
} State08121D20;

extern State08121D20 *data_020159CC;

/* Complete [0x08121D20, 0x08121D34), 20 bytes.
 * 03 4A 12 68 80 00 14 32 12 18 11 60 70 47 00 00 CC 59 01 02
 */
void func_08121D20(u32 index, void *value)
{
    data_020159CC->tasks[index] = value;
}
