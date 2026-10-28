#include "ffta.h"

/* 0x08121BF4..0x08121C18: 36 bytes. */
typedef struct {
    u8 unknown_00[0x54];
    void *object;
} ObjectState;

extern ObjectState *data_020159CC;
extern void *func_08096D7C(void);
extern void *func_0809D90C(void *);

void func_08121BF4(void)
{
    if (data_020159CC->object == 0)
        data_020159CC->object = func_0809D90C(func_08096D7C());
}
