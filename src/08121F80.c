#include "ffta.h"

typedef struct {
    void *manager;
    u8 unknown_04[0x10];
    void *tasks[16];
} State;

extern State *data_020159CC;
extern void func_080058A4(void *manager, void *task);

/* Complete [0x08121F80, 0x08121FB8): 56 bytes, 24 instructions. */
void func_08121F80(void)
{
    s32 index;
    for (index = 0; index < 16; index++) {
        void *task = data_020159CC->tasks[index];
        if (task != 0) {
            func_080058A4(data_020159CC->manager, task);
            data_020159CC->tasks[index] = 0;
        }
    }
}
