#include "ffta.h"

typedef struct Context0809EA60 Context0809EA60;

extern Context0809EA60 data_0200F770;
extern void func_0809EA60(Context0809EA60 *context, u32 value);

/* 0x0809F9A8..0x0809F9C0: 24 bytes, including the literal pool. */
Context0809EA60 *func_0809F9A8(u32 value)
{
    Context0809EA60 *context = &data_0200F770;

    func_0809EA60(context, value);
    return context;
}
