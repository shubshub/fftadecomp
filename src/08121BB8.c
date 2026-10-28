#include "ffta.h"

/* Target: complete [0x08121BB8, 0x08121BD0), 24 bytes including literal. */
typedef struct {
    void *manager;
} State08121BB8;

extern State08121BB8 *data_020159CC;
extern void func_080058A4(void *manager, void *task);

void func_08121BB8(void *task)
{
    func_080058A4(data_020159CC->manager, task);
}
