#include "ffta.h"

/* Target: complete [0x08121C18, 0x08121C38), 32 bytes including literal. */
typedef struct {
    u8 unknown_00[0x54];
    void *handle;
} State08121C18;

extern State08121C18 *data_020159CC;
extern void func_0809D938(void *);

void func_08121C18(void)
{
    if (data_020159CC->handle != 0) {
        func_0809D938(data_020159CC->handle);
        data_020159CC->handle = 0;
    }
}
