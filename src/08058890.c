#include "ffta.h"

/* 0x08058890..0x08058908: 120 bytes. */
typedef struct {
    u8 unknown_00[0x1414];
    u8 context;
} DisplayState;

extern DisplayState *data_0200F428;
extern void func_0802B554(void *context, u32 id);

void func_08058890(u8 value)
{
    if (value < 30)
        func_0802B554(&data_0200F428->context, 0x9F);
    else if (value < 80)
        func_0802B554(&data_0200F428->context, 0xA0);
    else if (value < 100)
        func_0802B554(&data_0200F428->context, 0xA1);
    else
        func_0802B554(&data_0200F428->context, 0xA2);
}
