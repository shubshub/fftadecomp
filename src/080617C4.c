#include "ffta.h"

typedef struct {
    u8 selector;
    u8 unknown_01[0x4B];
    u8 result;
    u8 unknown_4d[7];
    u32 flags;
} DispatchState080617C4;

extern DispatchState080617C4 *data_0200F450;
extern void (*data_08393918[])(void);
extern void func_08011C60(void);
extern void func_08065028(u32 value);

/* 0x080617C4: 64 bytes; dispatch the selected state and return its result. */
u8 func_080617C4(void)
{
    u8 selector = data_0200F450->selector;

    data_08393918[selector]();
    if (data_0200F450->flags & 2)
        func_08011C60();
    func_08065028(0);
    return data_0200F450->result;
}
